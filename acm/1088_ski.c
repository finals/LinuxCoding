#include <stdio.h>
#define N 100

int map[N][N];
int cnt[N][N];
int now_max;

int get_length(int i, int j, int row, int column)
{
    int max = 0;
    if (i-1 >= 0 && map[i][j] < map[i-1][j]) {
        if(cnt[i-1][j] == 0)
            cnt[i-1][j] = get_length(i-1,j, row, column);
        if (cnt[i-1][j]  > max)
            max = cnt[i-1][j] ;
    }
    if (j+1 <column && map[i][j] < map[i][j+1]) {
        if (cnt[i][j+1] == 0)
            cnt[i][j+1] = get_length(i,j+1, row, column);
        if (cnt[i][j+1] > max)
            max = cnt[i][j+1];
    }
    if (i+1 < row && map[i][j] < map[i+1][j]) {
        if(cnt[i+1][j] == 0)
            cnt[i+1][j] = get_length(i+1,j, row, column);
        if (cnt[i+1][j] > max)
            max = cnt[i+1][j];
    }
    if (j-1 >= 0 && map[i][j] < map[i][j-1]) {
        if (cnt[i][j-1] == 0)
            cnt[i][j-1] = get_length(i,j-1, row, column);
        if (cnt[i][j-1] > max)
            max = cnt[i][j-1];
    }
    if (max+1 > now_max)
        now_max = max+1;
    return max+1;
}

int main()
{
    int i, j, max = 0;
    int row, column;
    scanf("%d %d", &row, &column);
    for (i = 0; i < row; ++i) {
        for(j = 0; j < column; ++j) {
            scanf("%d", &map[i][j]);
        }
    }
    for (i = 0; i < row; ++i) {
        for(j = 0; j < column; ++j) {
            if (cnt[i][j] == 0)
                cnt[i][j] = get_length(i, j, row,column);
        }
    }
    printf("%d\n", now_max);
    return 0;
}

