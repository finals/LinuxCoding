#include <stdio.h>

int main()
{
    double sum = 0.0, money;
    int i;
    for (i = 0; i < 12; ++i) {
        scanf("%lf", &money);
        sum += money;
    }
    printf("$%.2lf", sum/12);
    return 0;
}
