#include <stdio.h>
#include <pthread.h>

int count=0;

void thread(void)
{
    
}

int main(void)
{
    pthread_t tid;
    int i, ret;

    for( i = 0; i < 100000; ++i) {
        ret = pthread_create(&tid, NULL, (void *)thread, NULL);
        if ( ret != 0 ) {
            printf("Create pthread error!\n");
            return 1;
        }
        count++;
        pthread_join(tid, NULL);
    }
 
    printf("count: %d\n", count);
    return 0;
}
