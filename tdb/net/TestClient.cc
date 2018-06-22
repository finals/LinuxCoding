#include <string.h>
#include <iostream>

#include "CSocket.h"

int main(int argc, char *argv[])
{
    const char *ip = "192.168.8.15";
    char *str = "ABCDEFGHI";
    net::CSocket *socket = new net::CSocket();
    std::cout << "000" << std::endl;
    socket->setAddr(ip, 9999);
    std::cout << "111" << std::endl;
    socket->Connect();
    std::cout << "client connect server..." << std::endl;

    if (!socket->Send(str, strlen(str))) {
        std::cout << "send error" << std::endl;
    }

    char recvbuf[256];
    memset(recvbuf, 0, sizeof(recvbuf));
    if (!socket->Recv(recvbuf, 16, 0)) {
        std::cout << "recv error" << std::endl;
    }

    std::cout << recvbuf << std::endl;
    getchar();

    return 0;
}

