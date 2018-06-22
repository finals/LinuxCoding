#include <string.h>
#include <iostream>

#include "CSocket.h"

int main(int argc, char *argv[])
{
    net::CServSocket servSocket;
    net::CSocket *socket;

    if (!servSocket.Listen(9999)) {
        std::cout << "listen error" << std::endl;
    }

    while (true) {
        if (!(socket = servSocket.Accept())) {
            std::cout << "accept error" << std::endl;
            return -1;
        }
        
        if (socket->getSockfd() > 0) {
            std::cout << "client (" << socket->getCliIp() << ")" << std::endl;
            char recvbuf[11];
            memset(recvbuf, 0, sizeof(recvbuf));
            socket->Recv(recvbuf, 10, 0);
            std::cout << recvbuf << std::endl;
            char sendbuf[256];
            memset(sendbuf, 0, sizeof(sendbuf));

            strcpy(sendbuf, "come from server");
            if (!socket->Send(sendbuf, 16)) {
                std::cout << "send error" << std::endl;
            }
        }
    }
    
    return 0;
}
