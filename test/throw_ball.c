#include <stdio.h>
#include <malloc.h>

int ft[101] = {0}; 

int max_num(int a, int b)
{
    return a > b ? a : b;
}

void print_array(int *arr, int len)
{
    for (int i = 0; i < len; ++i) {
        printf("%d ", arr[i]);
    }
    
    printf("\n");
}


int throw_ball(int N)
{
   int i = 0, j = 0;
   int min = 0, max = 0;
   
   ft[0] = 1;
   ft[1] = 1;

   for (i = 2; i < N; ++i) { //设楼层高为i，ft[i]表示i层楼找到临界楼层的最少次数
       min = -1;
       for (j = 1; j < i; ++j) { //从2楼开始，直到i层，算出最小次数
           max = max_num(j, 1+ft[i-j]);
           if (min == -1 || min > max) {
               min = max;
           }
       }
       ft[i] = min;
   }

   return ft[N-1];
}

int main(void)
{
    int a = throw_ball(109);

    printf("%d\n", a);
    return 0;
}
