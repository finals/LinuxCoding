#include <stdio.h>

#define NOT_FOUND -999

int binary_search(int *arr, int len, int key)
{
    int l = 0, r = len - 1, mid = 0;

    while (l <= r) {
        mid = (l + r) >> 1;
        if (arr[mid] == key) {
            return mid;
        }
        if (arr[mid] > key) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    return NOT_FOUND;
}

int main(void)
{
    int arr[] = {1,3,6,8,9,12,14,18,24,39,45,68,77,99};
    int len = sizeof(arr) / sizeof(int);

    int key = 1;

    int pos = binary_search(arr, len, key);

    if (pos == NOT_FOUND) {
        printf("key: %d Not Found\n", key);
    } else {
        printf("key: %d pos: %d\n", key, pos);
    }
    
    return 0;
}
