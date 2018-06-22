#include <stdio.h>

void print_array(int *arr, int len)
{
    for (int i = 0; i < len; ++i) {
        printf("%d ", arr[i]);
    }
    
    printf("\n");
}


int partition(int *arr, int low, int high)
{
    int key = arr[low];
    int l = low, h = high;

    while (l < h) {
        while (l < h && arr[h] >= key)
            h--;

        arr[l] = arr[h];

        while (l < h && arr[l] <= key) 
            l++;

        arr[h] = arr[l];
    }

    arr[l] = key;

    return l;
}

void bottom_k(int *arr, int len, int k)
{
    int l = 0, h = len - 1;
    int idx = partition(arr, 0, len-1);
    print_array(arr, len);

    while (idx != k - 1) {
        if (idx < k - 1) {
            idx = partition(arr, idx + 1, h);
            print_array(arr, len);
        }

        if (idx > k - 1) {
            idx = partition(arr, l, idx - 1);
            print_array(arr, len);
        }
    }
}

int main(void)
{
    int arr[] = {4,5,1,6,2,7,3,8};
    int len = sizeof(arr)/sizeof(int);

    bottom_k(arr, len, 5);

    print_array(arr, 5);
}
