#include <stdio.h>
#include <memory.h>

#define MAXIN 75
char board[MAXIN+2][MAXIN+2]; //��������
int minstep, w, h, to[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}}; //���巽��
int mark[MAXIN+2][MAXIN+2]; //����������

void Search(int now_x, int now_y, int end_x, int end_y, int step, int f)
{
    int i, x, y;
    if (step > minstep) 
        return; //��ǰ·��������ministep������ -> �Ż�����
    if (now_x == end_x && now_y == end_y) {
        if (minstep > step) //������С·����
            minstep = step;
        return;
    }
    for(i = 0; i <4; ++i) {  //ö����һ���ķ���
        int x = now_x + to[i][0];  //�õ��µ�λ��
        int y = now_y + to[i][1];
        if( (x > -1) && (x < w+2) && (y > -1) && (y < h + 2)
            && (((board[y][x]==' ') && (mark[y][x]==0)) || ((x == end_x)
            && (y == end_y) && (board[y][x] == 'X')))) { //�����λ����Ч
              mark[y][x] = 1;  //��Ǹ�λ���Ѿ�����

              if( f == i)    //��һ������͵�ǰ������ͬ,�ݹ�����ʱstep����
                  Search(x, y, end_x, end_y, step, i);
              else           //����ı䣬step+1
                  Search(x, y, end_x, end_y, step+1, i);
              mark[y][x] = 0;  //���ݣ���λ��δ���߹�
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
        for(i = 1; i <= h; ++i) { //������εĲ���
            getchar();
            for(j = 1; j <= w; j++)
                board[i][j] = getchar();
        }
        //�ھ��ΰ����������һȦ����
        for(i = 0; i <=w; ++i)
            board[h+1][i+1] = ' ';
        for(i = 0; i <= h; ++i)
            board[i+1][w+1] = ' ';

        int begin_x, begin_y, end_x, end_y, count = 0;
        while(scanf("%d %d %d %d", &begin_x, &begin_y, &end_x, &end_y)
            && begin_x > 0) { //���������յ�
              count++;
              minstep = 100000;
              memset(mark, 0, sizeof(mark));
              //�ݹ�����
              Search(begin_x, begin_y, end_x, end_y, 0, -1);
              //������
              if(minstep < 100000)
                  printf("Pair %d: %d segments.\n", count, minstep);
              else 
                  printf("Pair %d: impossible.\n", count);
        }
        printf("\n");
    }
    return 0;
}
