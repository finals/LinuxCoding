#include <stdlib.h>
#include <stdio.h> 
int main()
{
    int *p1 = malloc(4);
    int *p2 = malloc(4);
    int *p3 = malloc(4);
    
    *p1 = 1;
    *(p1+1) = 2;
    *(p1+2) = 3;    
    *(p1+3) = 4;
    *(p1+4) = 5;
    *(p1+5) = 6;
    *(p1+6) = 7;
    *(p1+7) = 8;
    *(p1+8) = 9;
    
    printf("%d\n", *p2);
    return 0;
}

