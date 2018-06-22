#include <string.h>
#include <iostream>
#include <map>

#include "CSocketEvent.h"

int main(int argc, char *argv[])
{
    net::CServSocket servSocket;
    net::CSocketEvent socketEvent;
    std::map<int, net::CSocket*> socketMap;

    if (!servSocket.Listen(9999)) {
        std::cout << "listen error" << std::endl;
        return -1;
    }

    if (!socketEvent.eventAdd(&servSocket, true, false)) {
        std::cout << "epoll add error" << std::endl;
        return -1;
    }

    while (true) {
        int nevents = socketEvent.waitEvents(1000);
        for (int i = 0; i < nevents; ++i) {
            if (socketEvent.events[i].data.fd == servSocket.getSockfd()) {
                net::CSocket *socket = NULL;
                if ((socket = servSocket.Accept()) == NULL) {
                    std::cout << "accept error" << std::endl;
                    break;
                }

                std::cout << "accept event trigger: " << socket->getSockfd() << std::endl;
                
                socketEvent.eventAdd(socket, true, false);
                socketMap[socket->getSockfd()] = socket;
            } 
            else if (socketEvent.events[i].events & EPOLLIN) {
                int sockfd = socketEvent.events[i].data.fd;
                std::cout << "read event trigger: " << sockfd << std::endl;
                net::CSocket *socket = socketMap[sockfd];


                char recvbuf[11];
                memset(recvbuf, 0, sizeof(recvbuf));
                socket->Recv(recvbuf, 10, 0);
                std::cout << recvbuf << std::endl;
                socketEvent.eventSet(socket, false, true);
            } 
            else if (socketEvent.events[i].events & EPOLLOUT) {
                int sockfd = socketEvent.events[i].data.fd;
                std::cout << "write event trigger: " << sockfd << std::endl;
                net::CSocket *socket = socketMap[sockfd];
       
                char sendbuf[256];
                memset(sendbuf, 0, sizeof(sendbuf));
                strcpy(sendbuf, "come from server");
                if (!socket->Send(sendbuf, 16)) {
                    std::cout << "send error" << std::endl;
                }
                socketEvent.eventSet(socket, true, false);
                delete socket;
            }
        }
    }
    return 0;
}
