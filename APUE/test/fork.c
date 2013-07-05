#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#define P_NUMBER 255
#define COUNT  1000
#define TEST_LOGFILE "logFile.log"
FILE *logFile = NULL;

char *s = "hello linux";

int main(void)
{
    int i = 0, j = 0;
    logFile = fopen(TEST_LOGFILE, "a+"); 
    for (i = 0; i < P_NUMBER; ++i) {
        if (fork() == 0) {
            for( j = 0; j < COUNT; ++j) {
                printf("[%d]%s\n", j, s);
            }
            exit(0);
        }
    }
    for( i = 0; i < P_NUMBER; ++i) {
        wait(0);
    }

    printf("Test Finished.\n");
    return 0;
}
