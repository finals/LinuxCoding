#include <stdio.h>
#include <malloc.h>

int dice(int n, int s)
{
    int **dp = malloc(sizeof(int *)*(n+1));
    int i = 0, j = 0, k = 0;
    int result = 0;

    for (i = 0; i <= n; ++i) {
        dp[i] = malloc(sizeof(int)*(s+1));
    }

    for (i = 0; i <= n; ++i) {
        dp[i][0] = 0;
    }

    for (j = 1; j <= s; ++j) {
        dp[0][j] = 0;
        dp[1][j] = 1;
    }

    for (i = 2; i <= n; ++i) {
        for (j = 1; j <= s; ++j) {
            dp[i][j] = 0;
            for (k = 1; k <= j; ++k) {
                dp[i][j] += dp[i-1][j-k];
            }
        }
    }

    result = dp[n][s];

    for (i = 0; i <= n; ++i) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void)
{
    int n = 2, s = 6;
    printf("n: %d, s: %d, dice: %d\n", n, s, dice(n,s));
    return 0;
}
