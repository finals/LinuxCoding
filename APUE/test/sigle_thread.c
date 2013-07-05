#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

#define ORANGE_MAX_VALUE 1000000
#define APPLE_MAX_VALUE     100000000
#define MSECOND   1000000

struct apple 
{
    unsigned long long a;
    unsigned long long b;
};

struct orange 
{
    int a[ORANGE_MAX_VALUE];
    int b[ORANGE_MAX_VALUE];
};

int main(void)
{
    struct apple test_apple;
    struct orange test_orange={{0}, {0}}; 

    unsigned long long sum = 0, index = 0;
    struct timeval tstart, tend;
    float timeuse;

    test_apple.a = 0;
    test_apple.b = 0;

    gettimeofday(&tstart, NULL);

    for(sum = 0; sum < APPLE_MAX_VALUE; ++sum) {
        test_apple.a += sum;
        test_apple.b += sum;
    }

    for ( index = 0, sum = 0; index < ORANGE_MAX_VALUE; ++index) {
        sum += test_orange.a[index] + test_orange.b[index];
    }

    gettimeofday(&tend, NULL);

    timeuse = MSECOND*(tend.tv_sec - tstart.tv_sec) +
        tend.tv_usec - tstart.tv_usec;
    timeuse /= MSECOND;

    printf("main thread Used Time: %f\n", timeuse);

    printf("a = %llu, b = %llu, sum = %llu\n", test_apple.a, test_apple.b, sum);
    
    return 0;
}



