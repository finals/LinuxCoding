#include <stdio.h>
#define N 100
#define M 101

char map[N][M];

int main()
{
    int n, m;
    int i, j;
    int count = 0;
    scanf("%d %d", &n, &m);

    for (i = 0; i < n; ++i) {
        scanf("%s",  map[i]);
    }

    for(i = 0; i < n; ++i) {
        for(j = 0; j < m; ++j) {
            if(i == 0 && map[i][j] == 'W' && j > 1 &&  map[i][j-1] != 'W')
                count++;
            if( i > 0 && map[i][j] == 'W' && map[i-1][j] != 'W' &&
                j - 1 >=0 && map[i-1][j-1]!='W' && map[i][j-1] != 'W') {
                count++;
            }
        }
    }

    printf("%d\n", count);
    return 0;
}
