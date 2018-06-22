#include <stdio.h>

int rec_sub_set_sum(int *arr, int i, int s)
{
    if (s == 0) {
        return 1;
    }
    if (i == 0) {
        return arr[0] == s;
    }

    if (arr[i] > s) {
        return rec_sub_set_sum(arr, i - 1, s);
    }

    return rec_sub_set_sum(arr, i - 1, s - arr[i]) || rec_sub_set_sum(arr, i - 1, s);
}

int for_sub_set_sum(int *arr, int len, int s)
{
   int subset[len+1][s+1];
   int i, j;
   for (i = 0; i <= len; i++) {
       subset[i][0] = 1;
   }
   for (j = 0; j <= s; j++) {
       
   }
}

#define N 5

int main(void)
{
    int arr[N+1] = {3,34,4,12,11,21};
    int s = 9;
    printf("%d\n", rec_sub_set_sum(arr, N, s));
    return 0;
}
