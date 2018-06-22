#include <iostream>
#include <cstdio>
#include <string.h>
#include <unistd.h>

#include "CSocketEvent.h"

namespace net {

CSocketEvent::CSocketEvent()
{
    if ((epfd = epoll_create(EpollSize)) < 0) {
        std::cout << "create epoll handle error" << std::endl;
        return;
    }

    memset(&events, 0, sizeof(struct epoll_event)*MaxEvents);
}

CSocketEvent::~CSocketEvent()
{
   if (epfd > 0) {
       close(epfd);
       epfd = -1;
   }
}

bool CSocketEvent::eventSet(CSocket *socket, bool readable, bool writeable)
{
    int sockfd = socket->getSockfd();
    if (sockfd < 0) {
        std::cout << "eventSet the socket fd error" << std::endl;
        return false;
    }

    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events |= EPOLLET; 
    if (readable) {
        ev.events |= EPOLLIN;
    }
    if (writeable) {
        ev.events |= EPOLLOUT;
    }
    ev.data.fd = sockfd;
    return (0 == epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev));
}

bool CSocketEvent::eventAdd(CSocket *socket, bool readable, bool writeable)
{
    int sockfd = -1;
    if (socket->setNonBlock(true)) {
        sockfd = socket->getSockfd();
    }

    if (sockfd < 0) {
        std::cout << "eventAdd the socket fd error" << std::endl;
        return false;
    }

    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events |= EPOLLET;
    if (readable) {
        ev.events |= EPOLLIN;
    }
    if (writeable) {
        ev.events |= EPOLLOUT;
    }
    ev.data.fd = sockfd;
    return (0 == epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev));
}

bool CSocketEvent::eventDel(CSocket *socket)
{
    int sockfd = socket->getSockfd();
    if (sockfd < 0) {
        std::cout << "eventDel the socket fd error" << std::endl;
        return false;
    }

    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = 0;
    return (0 == epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, &ev));
}

int CSocketEvent::waitEvents(int timeout)
{
    return epoll_wait(epfd, events, MaxEvents, timeout);
}

} //namespace net
