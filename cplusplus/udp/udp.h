#ifndef __UDP_H__
#define __UDP_H__

#include<sys/types.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace udp {

class UDPContex {
protected:
    int sockfd;
    struct sockaddr_in addr;
    struct sockaddr_in peer;
};

class UDPServer : public UDPContex {
public:
    UDPServer(const char *ip, uint16_t port);
    ~UDPServer();

    int Sendto(const void *buf, size_t len, int flags);
    int Recvfrom(void *buf, size_t len, int flags);
};

class UDPClient : public UDPContex {
public:
    UDPClient(const char *ip, uint16_t port);
    ~UDPClient();

    int Sendto(const void *buf, size_t len, int flags);
    int Recvfrom(void *buf, size_t len, int flags);
};


} //namespace udp

#endif //__UDP_H__
