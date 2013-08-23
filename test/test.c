#include <stdio.h>

struct sdslen {
    int len;
    int free;
    char buf[];
};

char buf[]; 

int main()
{
    printf("%d\n", sizeof(struct sdslen));
    return 0;
}
