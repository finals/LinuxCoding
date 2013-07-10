#include <stdio.h>
int inputInt(const char *info)
{
    int r; //返回值
    printf("%s:", info);
    scanf("%d", &r);
    return r;
}
