#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <signal.h> 

#include <hiredis/hiredis.h>  
#include <hiredis/async.h>  
#include <hiredis/adapters/libevent.h> 

//命令执行后的回调函数
void getCallback(redisAsyncContext *c, void *r, void *privdata)
{
    redisReply *reply = r;
    if (reply == NULL) return;
    printf("argv[%s]: %s\n", (char*)privdata, reply->str);

    redisAsyncDisconnect(c);
}

//连接建立的回调函数
void connectCallback(const redisAsyncContext *c, int status)
{
    if (status != REDIS_OK) {
        printf("Error: %s\n", c->errstr);
        return;
    }
    printf("Connected...\n");
}

//连接断开的回调函数
void disconnectCallback(const redisAsyncContext *c, int status) 
{
    if (status != REDIS_OK) {
        printf("Error: %s\n", c->errstr);
        return;
    }
    printf("Disconnect...\n");
}

int main(int argc, char **argv)
{
    signal(SIGPIPE, SIG_IGN);
    struct event_base *base = event_base_new(); //建立libevent事件

    redisAsyncContext *c = redisAsyncConnect("127.0.0.1", 6379); //新建异步连接
    if (c->err) {
        //Let *c leak for now...
        printf("Error: %s\n", c->errstr);
        return 1;
    }

    redisLibeventAttach(c, base); //将连接添加到libevent事件处理
    redisAsyncSetConnectCallback(c, connectCallback); //设置连接建立回调
    redisAsyncSetDisconnectCallback(c, disconnectCallback); //设置断开连接回调
    redisAsyncCommand(c, NULL, NULL, "SET key %b", argv[argc-1], strlen(argv[argc-1])); //发送set命令
    redisAsyncCommand(c, getCallback, (char*)"end-1", "GET key"); //发送get命令
    event_base_dispatch(base); //开始libevent循环，注意在这一步之前redis是不会进行连接的，前边调用的命令发送函数也没有真正发送命令
    return 0;
}

