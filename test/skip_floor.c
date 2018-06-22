#include <stdio.h>
#include <malloc.h>

int skip_floor(int n)
{
    int i = 0;
    int *sf = malloc(sizeof(int)*n);

    sf[0] = 1;
    sf[1] = 2;
    
    for (i = 2; i < n; ++i) {
        sf[i] = sf[i-1] + sf[i-2];
    }
    
    return sf[n-1];
}

int Fib(int n)  
{  
    if (n <= 0)  
    {  
        return -1;  
    }  
  
    if (1 == n)  
    {  
        return 1;  
    }  
    else if (2 == n)  
    {  
        return 2;  
    }  
    else  
    {  
        return Fib(n - 1) + Fib(n - 2);  
    }  
}  


int main(void)
{
    int a = skip_floor(30);
    int b = Fib(30);
    printf("skip type: %d %d\n", a, b);

    return 0;
}
