#ifndef __TDB_CSOCKET_H__
#define __TDB_CSOCKET_H__

#include <netinet/in.h>

namespace net {

class CSocket {
public:
    CSocket();
    virtual ~CSocket();

    std::string getLocalAddr();
    std::string getCliIp();
    int getSockfd() { return sockfd; }
    bool Close();
    bool Connect();
    bool Send(char *sendbuf, int len);
    bool Recv(char *recvbuf, int len, int timeout);

    bool setSoLinger(bool dolinger, int seconds);
    bool setIntOptions(int option, int value);
    bool setTimeout(int option, int milliseconds);
    bool setNonBlock(bool innonsocket);
    bool setNoDelay(bool nodelay);

    bool setUp(int sockfd, struct sockaddr_in *addr);
    bool setAddr(const char *addr, int port);

protected:
    int sockfd;
    char ip[20];
    struct sockaddr_in sockAddr;
    CSocket(const CSocket &);
    CSocket &operator=(const CSocket&);
};

class CServSocket : public CSocket {
public:
    CServSocket();
    virtual ~CServSocket();

    CSocket *Accept();
    bool Listen(int port);

private:
    bool Close();
};

class CCliSocket {
public:
    CCliSocket();
    virtual ~CCliSocket();
    bool Connect(const char *ip, int port);
    bool Send(char *sendbuf, int len);
    bool Recv(char *recvbuf, int len);

private:
    bool Close();
private:
    int clisockfd;
};

} //namespace net

#endif  /* __TDB_CSOCKET_H__ */