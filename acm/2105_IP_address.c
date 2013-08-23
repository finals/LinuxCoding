#include <stdio.h>

int main()
{
    int sum;
    int i,times;
    char str[33] = {0};
   scanf("%d", &times);

   while(times--) {
        scanf("%s", str);
        for(i = 0, sum = 0; i <= 32; ++i) {
            if(str[i] == '\0')
                printf("%d\n", sum);
            else if(i != 0 && i % 8== 0) {
                printf("%d", sum);
                printf(".");
                sum = 0;
            }
            if(str[i] == '1') {
                sum = sum + (1<<(7-i%8));
            }
        }
   }
}
