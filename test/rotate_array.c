#include <stdio.h>

int get_min_in_rotate_array(int *arr, int len)
{
    int low = 0, high = len - 1;
    int mid = 0;

    while (low < high-1) {
        mid = (low + high) >> 1;

        if (arr[mid] <= arr[high]) {
           high = mid;
           continue;
        }

        if (arr[mid] >= arr[low]) {
            low = mid;
            continue;
        }
    }

    printf("low: %d high: %d mid: %d\n", low, high, mid);
    return arr[high];
}

int min_rotate_array(int *arr, int len)
{
    int l = 0, h = len - 1;
    int mid = 0;

    while (l < h-1) {
        mid = (l + h) >> 1;
        if (arr[h] >= arr[mid]) {
            h = mid;
            continue;
        }

        if (arr[l] <= arr[mid]) {
            l = mid;
            continue;
        }
    }

    return arr[h];
}

int main(void)
{
    int arr[] = {3,4,5,6,7,1};
    printf("%d\n", min_rotate_array(arr, 6));
    return 0;
}
