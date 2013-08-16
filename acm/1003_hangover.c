#include <stdio.h>

int main()
{
    int count = 0, i;
    float c, s;
    while(1){
        scanf("%f",&c) ;
        if ( c >= -0.000001 && c <= 0.000001)
            break;
        for(s = 0.0, i = 2, count = 0; s - c < 0.000001; ++i) {
            s += 1.0/i;
            count++;
        }
        printf("%d card(s)\n", count);
    }
    return 0;
}
