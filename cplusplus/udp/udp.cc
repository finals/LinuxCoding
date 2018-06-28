#include <unistd.h>
#include <strings.h>
#include <sys/socket.h>
#include <string.h>
#include <iostream>

#include "udp.h"

namespace udp {

UDPServer::UDPServer(const char *ip, uint16_t port)
{
    //设置地址
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (ip == NULL)
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
    else 
        addr.sin_addr.s_addr = inet_addr(ip);

    //创建socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        //throw exception
        std::cerr << "create socket error" <<std::endl;
    }

    if (bind(sockfd,(struct sockaddr*)&addr,sizeof(addr)) < 0) {
        std::cerr << "bind socket error" << std::endl;
    }
}

UDPServer::~UDPServer()
{
    ::close(sockfd);
}

int UDPServer::Sendto(const void *buf, size_t len, int flags = 0)
{
    int nbytes = ::sendto(sockfd, buf, len, flags, (struct sockaddr *)&peer, sizeof(peer));
    if (nbytes < 0) {
        std::cerr << "sendto error" << std::endl;
    }
    return nbytes;
}

int UDPServer::Recvfrom(void *buf, size_t len, int flags = 0)
{ 
    socklen_t addr_len = sizeof(peer);
    int nbytes = ::recvfrom(sockfd, buf, len, flags,  (struct sockaddr *)&peer, &addr_len);
    if (nbytes < 0) {
        std::cerr << "recvfrom error" << std::endl;
    }

    return nbytes;
}


UDPClient::UDPClient(const char *ip, uint16_t port)
{
    //设置地址
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    //创建socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        //throw exception
        std::cerr << "create socket error" <<std::endl;
    }
}

UDPClient::~UDPClient()
{
    ::close(sockfd);
}

int UDPClient::Sendto(const void *buf, size_t len, int flags = 0)
{
    int nbytes = ::sendto(sockfd, buf, len, flags, (struct sockaddr *)&addr, sizeof(addr));
    if (nbytes < 0) {
        std::cerr << "sendto error" << std::endl;
    }
    return nbytes;
}

int UDPClient::Recvfrom(void *buf, size_t len, int flags = 0)
{ 
    socklen_t addr_len = sizeof(peer);
    int nbytes = ::recvfrom(sockfd, buf, len, flags,  (struct sockaddr *)&peer, &addr_len);
    if (nbytes < 0) {
        std::cerr << "recvfrom error" << std::endl;
    }

    return nbytes;
}

} //namespace udp
