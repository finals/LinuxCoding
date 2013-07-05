#define _GNU_SOURCE
#include <pthread.h>

#include <sys/time.h>

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <unistd.h>

#include <sys/syscall.h>

#include <sched.h>
#include <ctype.h> 
#include <string.h>





#define ORANGE_MAX_VALUE 1000000
#define APPLE_MAX_VALUE 100000000
#define MSECOND 1000000

pthread_t gettid()
{
    return syscall(SYS_gettid);
}

struct apple {
    unsigned long long a;
    unsigned long long b;
};

struct orange {
    int a[ORANGE_MAX_VALUE];
    int b[ORANGE_MAX_VALUE];
};

struct apple ts_apple;
struct orange ts_orange;

int cpu_nums;
cpu_set_t mask;

inline int set_cpu(int i)
{
    CPU_ZERO(&mask);

    if ( 2 <= cpu_nums) {
        CPU_SET(i, &mask);

        if ( -1 == sched_setaffinity(gettid(), sizeof(&mask), &mask))
        {
            return -1;
        }    
    }
    return 0;
}

void * add(void *x)
{
    int i;
    if (-1 == set_cpu(1)) {
        return NULL;
    }

    unsigned long long sum = 0, index = 0;
    for(sum = 0; sum < APPLE_MAX_VALUE; ++sum) {
        ((struct apple *)x)->a += sum;
        ((struct apple *)x)->b += sum;
    }

    return NULL;
}

int main(void)
{
    pthread_t ThreadA;
    unsigned long long sum=0, index=0;
    struct timeval tstart, tend;
    float timeuse;
    int i;

    ts_apple.a = 0;
    ts_apple.b = 0;

    cpu_nums = sysconf(_SC_NPROCESSORS_CONF);

    if ( -1 == set_cpu(0) ) {
        return -1;
    }

    gettimeofday(&tstart, NULL);

    pthread_create(&ThreadA, NULL, add, &ts_apple);

    for(index = 0; index < ORANGE_MAX_VALUE; ++index) {
        sum += ts_orange.a[index] + ts_orange.b[index];
    }

    pthread_join(ThreadA, NULL);
    gettimeofday(&tend, NULL);

    timeuse=MSECOND*(tend.tv_sec - tstart.tv_sec) + 
        tend.tv_usec - tstart.tv_usec;
    timeuse /= MSECOND;

    printf("dual thread Used Time: %f\n", timeuse);
    printf("a = %llu, b = %llu, sum = %llu\n", ts_apple.a, ts_apple.b, sum);
    
    return 0;
}

