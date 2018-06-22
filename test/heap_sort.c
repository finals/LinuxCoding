#include <stdio.h>

void swap(int *arr, int left, int right) {
    int tmp = arr[left];
    arr[left] = arr[right];
    arr[right] = tmp;
}

void adjust_heap(int *arr, int len)
{
    int i = 0, left = 0, right;

    for (i = (len >> 1) - 1; i >= 0; --i) {
        left = (i << 1) + 1;
        right = left + 1;

        if (arr[left] > arr[i]) {
            swap(arr, left, i);  
        }

        if (right < len && arr[right] > arr[i]) {
            swap(arr, i, right);
        }
    }
}

void heap_sort(int *arr, int len) 
{
    int i = 0;

    for (i = len - 1; i >= 0; --i) {
        adjust_heap(arr, i+1);

        swap(arr, 0, i);
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
    int arr[10] = {5,1,9,4,8,6,11,2,7,3};
    heap_sort(arr, 10);

    print_array(arr, 10);
    return 0;
}
