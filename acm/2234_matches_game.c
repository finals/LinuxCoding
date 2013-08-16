#include <stdio.h>

int main()
{
    int s, n, i, t;
    while ( scanf("%d", &n) != EOF ) {
        scanf("%d", &s);
        for (i = 1; i < n; ++i) {
            scanf("%d", &t);
            s ^=t;
        }
        if ( s )
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
