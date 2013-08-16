#include <stdio.h>

int main(void)
{
    unsigned int k, n, sum, x, c;

   scanf("%d", &c);

   while ( c-- ) {
        if (scanf("%d", &x) == EOF || x <= 0)
            return 0;

        for (k = 31, sum = 1<<k; k >=0; --k) {
            sum = sum>>1;
            if ( x >= sum && x % sum == 0 ) {
                break;
            }
        }

        for ( n = 0, sum = 0; n < k-1; ++n) {
            sum += 1<<n;
        }

        printf("%d %d\n", x-sum, x+sum);
   }
   
}
