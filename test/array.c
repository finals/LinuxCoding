#include <stdio.h>

int maxsum_continue_sub_array(int *arr, int len, int *start, int *end)
{
    int max = 0, cur = 0;
    int i = 0;

    for (i = 0; i < len; ++i) {
        cur += arr[i];

        if (cur < 0) {
            cur = 0;
            *start = i + 1;
        }
        if (max < cur) {
            max = cur;
            *end = i;
        }
    }

    return max;
}

int main(void)
{
    int arr[] = {1,-2,3,10,-4,7,2,-5};
    int len = sizeof(arr)/sizeof(int);
    int start = 0, end = 0;

    int max = maxsum_continue_sub_array(arr, len, &start, &end);
    printf("max: %d range: %d - %d\n", max, start, end);
}
