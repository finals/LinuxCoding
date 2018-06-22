#include <stdio.h>

const int C = 5;
const int R = 16;

int charge() 
{
    int i = 0, j = 0;
    int value[] = {1, 2, 5, 9, 10};
    int coins[C+1][R+1]; 

    for (i = 0; i <= C; ++i) {
       coins[i][0] = 0;
    }

    for (j = 0; j <= R; ++j) {
       coins[0][j] = 999999;
    }

    for (i = 1; i <= C; ++i) {    //i表示参加找零的硬币的种类1~i种硬币
        for(j = 1; j <= R; ++j) { //j表示需要找零的钱数
            if (j < value[i-1]) { //i-1对应数组下标
                coins[i][j] = coins[i-1][j];
                continue;
            }

            if (coins[i-1][j] > coins[i][j-value[i-1]] + 1) {
                coins[i][j] = coins[i][j-value[i-1]] + 1;
            } else {
                coins[i][j] = coins[i-1][j];
            }
        }
    }

    return coins[C][R];
}

int main(void)
{
    printf("%d\n", charge());
 
    return 0;
}
