#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define P_NUMBER 255
#define COUNT 1000

const char *str = "hello linux";

void print_str(void)
{
    int i = 0;
    for (i = 0; i < COUNT; ++i) {
        printf("[%d]%s\n", i,str); 
    }
    pthread_exit(0);
}

int main(void)
{
    int i = 0;
    pthread_t pid[P_NUMBER];
    
    for(i=0; i < P_NUMBER; ++i) {
        pthread_create(&pid[i],NULL, (void *)print_str, NULL);
    }

    for(i = 0; i < P_NUMBER; ++i)
        pthread_join(pid[i], NULL);
    return 0;
}

