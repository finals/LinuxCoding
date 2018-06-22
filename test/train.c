/*
 *一列火车有n个车厢标记为1，2，3，4，5，6…n 
 *现在因为某些原因，需要调整车厢的相对顺序 
 *例如需要将车厢顺序调整为2，3，1，4，5，6…n 
 *由于车厢庞大，且车厢只能停留在铁轨上，所以不能随心所欲的调整相对顺序
 *
 *现在只能利用两条并行的铁轨对车厢的顺序进行调整 
 *
 */

#include <stdio.h>
#include <malloc.h>

const char *YES = "YES";
const char *NO  = "NO";

const char *tune_train(int n, int *after) {
    int *rail_one = malloc(sizeof(int) * n);
    int ai = 0, bi = 1;
    int one_head = 0, one_tail = 0;

    while ( ai < n ) {
        if (bi <= n && bi == after[ai]) {
            ai++;
            bi++;
            continue;
        }

        if (one_head < one_tail && rail_one[one_head] == after[ai]) {
            ai++;
            one_head++;
            continue;
        }

        if (one_tail < n) {
            rail_one[one_tail] = bi;
            one_tail++;
            bi++;
            continue;
        }

        break;
    }
     
    free(rail_one);

     if (one_head != one_tail) {
         return NO;
     }

    return YES;
}

#define N 3

int main(void) {
    //int after[5] = {3,4,2,1,5};
    //int n = 5;

    int after[N] = {3,1,2};

    printf("%s\n", tune_train(N, after));
    
    return 0;
}
