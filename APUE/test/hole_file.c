#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void)
{
    int fd;
    if ((fd = open("test.hole", O_RDWR | O_CREAT |O_TRUNC)) == -1) {
        printf("open failed.");
        return 1;
    }
    if (write(fd, buf1, 10) == -1) {
        printf("write failed.");
        return 1;
    }
    if ( lseek(fd, 16538, SEEK_SET) == -1 ) {
        printf("lseek failed.");
        return 1;
    }
    if ( write(fd, buf2, 10) == -1 ) {
        printf("write failed.");
        return 1;
    }
    return 0;
}

