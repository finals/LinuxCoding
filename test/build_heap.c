#include <stdio.h>

void swap(int *arr, int i, int j) 
{
    int tmp = arr[i]; 
    arr[i] = arr[j];
    arr[j] = tmp;
}

void adjust_heap(int *arr, int len)
{
    if (arr == NULL || len <= 0) return;

    int i = 0, r = 0;
    int lchild = 0;

    for (r = (len >> 1); r > 0; --r) {
    for (i = (len >> 1) - 1; i >= 0; --i) {
        lchild = (i << 1) + 1;

        if (arr[lchild] > arr[i]) {
            swap(arr, lchild, i);
        }
        
        if (lchild < len - 1) {
            if (arr[lchild+1] > arr[i]) {
                swap(arr, lchild+1, i);
            }
        }
        
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
    int arr[] = {1, 2, 3, 4, 5};

    adjust_heap(arr, 5);
    print_array(arr, 5);

    return 0;
}
