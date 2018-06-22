#ifndef __REDIS_CONTEXT__
#define __REDIS_CONTEXT__

#include <hiredis/hiredis.h>

class RedisCtx {
private:
    char *ip;
    int  port;
    redisContext *c;

public:
    RedisCtx(const char *ip, int port);
    ~RedisCtx();

    command(const char *format, ...);
};

#endif
