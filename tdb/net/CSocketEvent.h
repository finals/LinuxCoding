#ifndef __TDB_CSOCKET_EVENT_H__
#define __TDB_CSOCKET_EVENT_H__

#include <sys/epoll.h>

#include "CSocket.h"

namespace net {

const int MaxEvents = 256;
const int EpollSize = 500;

class CSocketEvent {
public:
    CSocketEvent();
    virtual ~CSocketEvent();
    bool eventSet(CSocket *socket, bool readable, bool writeable);
    bool eventAdd(CSocket *socket, bool readable, bool writeable);
    bool eventDel(CSocket *socket);
    int waitEvents(int timeout);
    struct epoll_event events[MaxEvents];

private:
    int epfd;
    CSocketEvent(const CSocketEvent &);
    CSocketEvent &operator=(const CSocketEvent &);
};

} //namespace net

#endif /* __TDB_CSOCKET_EVENT_H__ */