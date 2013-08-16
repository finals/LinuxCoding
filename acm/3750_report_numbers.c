#include <stdio.h>

#define N 64
#define NAME_LENGTH 15

char children_name[N][NAME_LENGTH];
int flag[N];

int main()
{
    int i, j, num, left;
    int w, s;
    
    scanf("%d",&num);
    left = num;
    for(i = 0; i < num; ++i) {
        scanf("%s\n", children_name[i]);
    }
    scanf("%d,%d", &w, &s);
    for(i = w-1, j = 1; left > 0;) {
        if( i >= num) {
            i = 0;
            while( flag[i] != 0 )
                i++;
        }
        if(flag[i] == 1){
            i++;
            continue;
        }
        if( j == s ) {
            printf("%s\n", children_name[i]);
            flag[i] = 1;
            left--;
            i++;
            j = 1;
        }
        else if (flag[i] == 0) {
            i++;
            j++;
        }
    }
    
    return 0;
}