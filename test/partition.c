#include <stdio.h>

void partition(int *arr, int len)
{
    if (arr == NULL || len <= 0) {
        return;
    }

    int l = 0, h = len - 1;

    while (l < h) {
        while (l < h && (arr[h] % 2) == 0) {
            h--;
        }
    
        while (l < h && (arr[l] % 2) != 0) {
            l++;
        }

        if (l < h) {
            int tmp = arr[l];
            arr[l] = arr[h];
            arr[h] = tmp;
        }
    }
}

void print_array(int *arr, int len)
{
    for (int i = 0; i < len; ++i) {
        printf("%d ", arr[i]);
    }
    
    printf("\n");
}

int main(void)
{
    int arr[] = {1,3,5,7,9,2,4,6,8};
    int len = sizeof(arr)/sizeof(int);
    partition(arr, len);
    print_array(arr, len);
    return 0;
}
