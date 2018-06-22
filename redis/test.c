#include <stdio.h>
#include <hiredis/hiredis.h>

int main(void)
{
    redisContext *conn = redisConnect("192.168.3.230", 6379);
    if (conn != NULL && conn->err) {
        printf("connection error: %s\n", conn->errstr);
        return 0;
    }

    redisReply *reply;
    reply = redisCommand(conn, "SET %s %s", "foo", "bar");
    freeReplyObject(reply);
 
    reply = redisCommand(conn, "GET %s", "foo");
    printf("%s\n", reply->str);
    freeReplyObject(reply);

    redisFree(conn);

    return 0;
}

