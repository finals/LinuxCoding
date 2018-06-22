#include <stdio.h>

#define max(x, y) (x) > (y) ? (x) : (y)

int package01(int *weight, int *value, const int N, const int W)
{
    if (weight == NULL || value == NULL || N <= 0 || W <= 0) {
        return 0;
    }

    int i = 0, j = 0;
    int F[N+1][W+1];

    for (i = 0; i <= N; ++i) {
        for(j = 0; j <= W; ++j) {
            F[i][j] = 0;
        }
    }

    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= W; ++j) {
            if (j >= weight[i-1]) {
                F[i][j] = max(F[i-1][j], F[i-1][j-weight[i-1]] + value[i-1]);
            } else {
                F[i][j] = F[i-1][j];
            }
        }
    }
    
    return F[N][W];
}

int package01x(int *weight, int *value, const int N, const int W)
{
    if (weight == NULL || value == NULL || N <= 0 || W <= 0) {
        return 0;
    }

    int i = 0, j = 0;
    int F[W+1];

    for(j = 0; j <= W; ++j) {
        F[j] = 0;
    }

    for (i = 0; i <= N; ++i) {
        for (j = W; j > 0; --j) {
            if (j >= weight[i-1]) {
                F[j] = max(F[j], F[j-weight[i-1]]+value[i-1]);
            }
        }
    }
    return F[W];
}


#define UNDEFINED ((1<<30) - 1)
int packagefull(int *weight, int *value, const int N, const int W)
{
    if (weight == NULL || value == NULL || N <= 0 || W <= 0) {
        return 0;
    }

    int i = 0, j = 0;
    int F[N+1][W+1];

    for (i = 0; i <= N; ++i) {
        for(j = 0; j <= W; ++j) {
            F[i][j] = 0;
        }
    }

    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= W; ++j) {
            if (j >= weight[i-1]) {
                F[i][j] = max(F[i-1][j], F[i][j-weight[i-1]]+value[i-1]);
            } else {
                F[i][j] = F[i-1][j];
            }
        }
    }

    return F[N][W];
}


int main(void)
{
    int weight[] = {2,2,6,5,4};
    int value[]  = {6,3,5,4,6};
    int maxv = packagefull(weight, value, 5, 10);
    printf("%d\n", maxv);
}
