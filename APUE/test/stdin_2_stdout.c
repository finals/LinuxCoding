#include <stdio.h>
#include <unistd.h>

#define BUFSIZE 4096

char buf[BUFSIZE];

int main(void)
{
    int n;
  
    if ( (n = read(STDIN_FILENO, buf, BUFSIZE) )== -1 ) {
        printf("read failed.");
        return 1;
    }

    if ( (n = write(STDOUT_FILENO, buf, n)) == -1) {
        printf("write failed.");
        return 1;
    }
    
    return 0;
}
