#include <stdio.h>
#define N 10000
int arr[N];
int main()
{
    int i, begin, end, temp, size;
    int max = 0, maxendinghere = 0;
    while(1) {
    scanf("%d", &size);
    if(!size)
        break;
    
    for(i =0; i < size; ++i) {
        scanf("%d", &arr[i]);
    }
    max = arr[0];
    maxendinghere = arr[0];
    temp=0;
    for(i = 1; i < size; ++i) {
        maxendinghere += arr[i];
        if(maxendinghere < 0) {
            temp = i+1;
            maxendinghere = 0;
        }
            
        if(max < maxendinghere){
                end = i;
                begin = temp;
                max = maxendinghere;
            }
        }
        printf("%d %d %d\n", max, arr[begin], arr[end]);
    }
    return 0;
}
