#include <stdio.h>
#include <memory.h>

#define MAXIN 75
char board[MAXIN+2][MAXIN+2]; //定义矩阵板
int minstep, w, h, to[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}}; //定义方向
int mark[MAXIN+2][MAXIN+2]; //定义标记数组

void Search(int now_x, int now_y, int end_x, int end_y, int step, int f)
{
    int i, x, y;
    if (step > minstep) 
        return; //当前路径数大于ministep，返回 -> 优化策略
    if (now_x == end_x && now_y == end_y) {
        if (minstep > step) //更新最小路径数
            minstep = step;
        return;
    }
    for(i = 0; i <4; ++i) {  //枚举下一步的方向
        int x = now_x + to[i][0];  //得到新的位置
        int y = now_y + to[i][1];
        if( (x > -1) && (x < w+2) && (y > -1) && (y < h + 2)
            && (((board[y][x]==' ') && (mark[y][x]==0)) || ((x == end_x)
            && (y == end_y) && (board[y][x] == 'X')))) { //如果新位置有效
              mark[y][x] = 1;  //标记该位置已经经过

              if( f == i)    //上一步方向和当前方向相同,递归搜索时step不变
                  Search(x, y, end_x, end_y, step, i);
              else           //方向改变，step+1
                  Search(x, y, end_x, end_y, step+1, i);
              mark[y][x] = 0;  //回溯，该位置未曾走过
        }
    }
}

int main()
{
    int Boardnum = 0;
    int i, j;
    while(scanf("%d %d", &w, &h)) {
        if(w == 0 && h == 0)
            break;
        Boardnum++;
        printf("Board #%d:\n", Boardnum);
        for (i = 0; i < MAXIN + 2; ++i)
            board[0][1] = board[i][0] = ' ';
        for(i = 1; i <= h; ++i) { //读入矩形的布局
            getchar();
            for(j = 1; j <= w; j++)
                board[i][j] = getchar();
        }
        //在矩形板最外层增加一圈格子
        for(i = 0; i <=w; ++i)
            board[h+1][i+1] = ' ';
        for(i = 0; i <= h; ++i)
            board[i+1][w+1] = ' ';

        int begin_x, begin_y, end_x, end_y, count = 0;
        while(scanf("%d %d %d %d", &begin_x, &begin_y, &end_x, &end_y)
            && begin_x > 0) { //读入起点和终点
              count++;
              minstep = 100000;
              memset(mark, 0, sizeof(mark));
              //递归搜索
              Search(begin_x, begin_y, end_x, end_y, 0, -1);
              //输出结果
              if(minstep < 100000)
                  printf("Pair %d: %d segments.\n", count, minstep);
              else 
                  printf("Pair %d: impossible.\n", count);
        }
        printf("\n");
    }
    return 0;
}
