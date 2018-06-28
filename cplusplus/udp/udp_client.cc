#include <iostream>
#include <string.h>

#include "udp.h"

int main(void)
{
    auto ctx = udp::UDPClient("127.0.0.1", 12345);

    char buf[1024];
    bzero(buf, sizeof(buf));

    strcpy(buf, "send something to server");
    int nbytes = ctx.Sendto(buf, strlen(buf) + 1, 0);
    if (nbytes <= 0) {
        return -1;
    }
    std::cout << "send " << nbytes << " bytes: " << buf <<std::endl;

    bzero(buf, sizeof(buf));
    nbytes = ctx.Recvfrom(buf, sizeof(buf), 0);
    if (nbytes <= 0) {
        return -1;
    }
    std::cout << "recv " << nbytes << " bytes: " << buf << std::endl;
    return 0;
}

