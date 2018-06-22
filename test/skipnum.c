#include <stdio.h>
#include <malloc.h>

int max_sum_with_skip_num(int *arr, int len) 
{
    int *ops = malloc(sizeof(int) * len);
    int result = 0, i = 0;

    ops[0] = arr[0];
    ops[1] = arr[1] > arr[0] ? arr[1] : arr[0];

    for (i = 2; i < len; i++) {
        ops[i] = ops[i-1];

        if (ops[i-2] + arr[i] > ops[i]) {
            ops[i] = ops[i-2] + arr[i];   
        }
        
    }

    result = ops[len-1];
    free(ops);
    return result;
}

#define LEN 7
#define max(x, y) (x) > (y) ? (x) : (y)
int max_skip_num(int *arr, int len)
{
    int F[LEN] = {0};
    int i = 0;
    if (arr == NULL || len <= 0) {
        return 0;
    }

    F[0] = arr[0];
    F[1] = max(arr[0], arr[1]);
    for (i = 2; i < len; ++i) {
        F[i] = max(F[i-1], F[i-2]+arr[i]);
    }

    return F[LEN-1];
}

int main(void) 
{
    int arr[LEN] = {1,2,4,1,7,8,3};
    printf("max sum: %d\n", max_skip_num(arr, LEN));
    return 0;
}
