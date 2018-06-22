#include <stdio.h>

void quick_sort(int *arr, int left, int right) 
{
    int x = arr[left];
    int l = left, h = right;

    if (left >= right) {
        return;
    }

    while (l < h) {
        //从高位找到一个大于哨兵x的位置
        while(arr[h] >= x && l < h) {
            h--; 
        }

        arr[l] = arr[h];

        //从低位找到一个小于哨兵x的位置
        while(arr[l] <= x && l < h) {
            l++;
        }

        arr[h] = arr[l];
    }

    arr[l] = x;
    quick_sort(arr, left, l-1);
    quick_sort(arr, l+1, right);
    
}

void swap(int *arr, int a, int b)
{
    int tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}

void sort(int *arr, int low, int high)
{
    int x = arr[low]; //哨兵
    int l = low, h = high;

    if (l >= h) return;

    while (l < h) {
       while (l < h && arr[h] >= x) {
           h--;
       }

       while (l < h && arr[l] <= x) {
           l++;
       }

       if (l < h)
           swap(arr, l, h);
    }

    arr[low] = arr[l]; 
    arr[l] = x;
    sort(arr, low, l-1);
    sort(arr, l+1, high);
}

int main(void) 
{
    int arr[] = {6, 1, 2, 7, 9, 5, 4, 3, 10, 8};
    int i = 0;
    sort(arr, 0, 9);

    for (i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}
