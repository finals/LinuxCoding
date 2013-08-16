#include <stdio.h>

int main(void)
{
    int n, x, y;
    scanf("%d", &n);
    while ( n-- ) {
        scanf("%d %d", &x, &y);
        if (x == y || x == y+2) {
            printf("%d\n", x+y-(x&1));  
            continue;
        }
        printf("No Number\n");
    }
    return 0;
}
