s#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int count = 0; //子进程创建成功数量
int fcount = 0; //子进程创建失败数量
int scount = 0; //子进程回收数量

/* 信号处理函数-子进程关闭收集 */
void sig_chld(int signo) 
{
    pid_t chldpid;
    int stat; 

    while( (chldpid=wait(&stat)>0)) {
         ++scount;
    }
}

int main(void)
{
    signal(SIGCHLD, sig_chld);
    int i;
    pid_t pid;

    for ( i = 0; i < 100000; ++i) {
        pid = fork();
        if ( pid == -1)
            ++fcount;
        else if (pid > 0)
            ++count;
        else if(pid == 0)
            exit(0);
    }
    
    printf("count: %d,  fcount: %d, scount: %d\n", count, fcount, scount);
    return 0;
}

