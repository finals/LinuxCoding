#include <stdio.h>

#define N 100
int triangle[N][N];
int dp[N][N];

int main()
{
    int rows;
    int i, j;
    int max;
    int all_max = 0;
    scanf("%d", &rows);
    for(i = 0; i < rows; ++i) {
        for(j = 0; j <= i; ++j) {
            scanf("%d", &triangle[i][j]);
        }
    }
    dp[0][0] = triangle[0][0];
    for(i = 1; i < rows; ++i) {
        for(j = 0; j <= i; ++j) {
            max = 0;
            if(j - 1 >= 0)
                max = dp[i-1][j-1]+triangle[i][j];
            if (dp[i-1][j]+triangle[i][j] > max)
                max = dp[i-1][j]+triangle[i][j];
            if (max > all_max)
                all_max = max;
            dp[i][j] = max;
        }
    }
    printf("%d\n", all_max);
    return 0;
}
