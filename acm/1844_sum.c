#include <stdio.h>

int main(void)
{
    int s, i, r;
    scanf("%d", &s);
    i =1; r = 0;
    while( 1 ) {
        r += i;
        if ( r < s || (r -s) % 2 == 1 )
            i++;
        else
            break;
    }

    printf("%d\n", i);
    return 0;
}
