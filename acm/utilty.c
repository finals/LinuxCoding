#include <stdio.h>

void print_2d_array(int arr[N][N], int len)
{
    int i, j;
    for(i = 0; i < len; ++i) {
        for(j = 0; j < len; ++j) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

