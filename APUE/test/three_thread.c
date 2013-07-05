#define _GNU_SOURCE
#include <sys/time.h>
#include <pthread.h>

#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/sysinfo.h>
#include<unistd.h>

#include<sched.h>
#include<ctype.h>
#include<string.h> 

#include <sys/syscall.h> /*此头必须带上*/

pid_t gettid()
{
    return syscall(SYS_gettid); 
}

#define ORANGE_MAX_VALUE 1000000
#define APPLE_MAX_VALUE 100000000
#define MSECOND 1000000

struct apple
{
    unsigned long long a;
   char c[32]; /*32,64,128*/
    unsigned long long b;
    pthread_rwlock_t rwLock;
};

struct orange
{
    int a[ORANGE_MAX_VALUE];
    int b[ORANGE_MAX_VALUE];
};

struct apple test;
struct orange test1;

int cpu_nums;
cpu_set_t mask;
     
inline int set_cpu(int i)
{
    CPU_ZERO(&mask);
    
    if(2 <= cpu_nums)
    {
        CPU_SET(i,&mask);
        
        if(-1 == sched_setaffinity(gettid(),sizeof(&mask),&mask))
        {
            return -1;
        }
    }
    return 0;
}

void* addx(void* x)
{
/*
    if(-1 == set_cpu(0))
    {
        return NULL;
    }
*/ 
    unsigned long long sum=0,index=0;
    pthread_rwlock_wrlock(&((struct apple *)x)->rwLock);
    for(sum=0;sum<APPLE_MAX_VALUE;sum++)
    {
        ((struct apple *)x)->a += sum;
    }
    pthread_rwlock_unlock(&((struct apple *)x)->rwLock);
    
    return NULL;
} 

void* addy(void* y)
{
/*  
  if(-1 == set_cpu(1))
    {
        return NULL;
    }
*/ 
    unsigned long long sum=0,index=0;
    pthread_rwlock_wrlock(&((struct apple *)y)->rwLock);
    for(sum=0;sum<APPLE_MAX_VALUE;sum++)
    {
        ((struct apple *)y)->b += sum;
    }
    pthread_rwlock_unlock(&((struct apple *)y)->rwLock);
    
    return NULL;
}

int main () 
{
    pthread_t ThreadA,ThreadB;
    unsigned long long sum=0,index=0;
    struct timeval tpstart,tpend;
    float timeuse;
/*    
    cpu_nums = sysconf(_SC_NPROCESSORS_CONF);
    
    if(-1 == set_cpu(0))
    {
        return -1;
    } 
 */   
    gettimeofday(&tpstart,NULL);
    
    pthread_create(&ThreadA,NULL,addx,&test);
    pthread_create(&ThreadB,NULL,addy,&test);

    for(index=0;index<ORANGE_MAX_VALUE;index++)
    {
        sum+=test1.a[index]+test1.b[index];
    }
    
    pthread_join(ThreadA,NULL);
    pthread_join(ThreadB,NULL);
    
    gettimeofday(&tpend,NULL);
    
    timeuse=MSECOND*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.
tv_usec;
    timeuse/=MSECOND;
    printf("thread thread,Used Time:%f\n",timeuse); 
    
    printf("a = %llu, b = %llu, sum=%llu\n",test.a,test.b,sum);
  
    return 0;
}

