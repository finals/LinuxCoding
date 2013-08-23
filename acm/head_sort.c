#include <stdio.h>

void swap_int(int *a, int *b)
{
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void HeapAdjust(int arr[], int s, int m)
{
    int i,pos;
    for(i = s; i > 0; --i)
    {
        if (2*i +1 <= m) {
            pos= arr[2*i] > arr[2*i+1] ? 2*i : (2*i+1);
        }
        else {
            pos = 2*i;
        }

        if (arr[pos] > arr[i])
            swap_int(&arr[pos], &arr[i]);   
    }
}

void HeapSort(int arr[], int len)
{
    int i;
    for( i = 1; i < len-1; ++i)
    {
        HeapAdjust(arr, (int)((len-i)/2), len-i);
        swap_int(&arr[1], &arr[len-i]);
    }
}

int main()
{
    int i;
    int arr[] = {0,5,1,9,3,7,8,8,6,2};
    HeapSort(arr, 10);
    for(i = 1; i < 10; ++i)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
