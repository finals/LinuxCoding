#include <stdio.h>

#define N 2000
#define INF 65535

int graph[N][N];
char truck_type[N][8];

int calcute_cost(char s1[8], char s2[8])
{
    int count = 0;
    while(*s1 != '\0') {
        if(*s1++ != *s2++)
            count++;
    }
    return count;
}


void print_2d_array(int arr[N][N], int len)
{
    int i, j;
    for(i = 0; i < len; ++i) {
        for(j = 0; j < len; ++j) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int  mini_span_tree_prim(int graph[][N], int nodes_count)
{
    int lowcost[N];
    int adjvec[N];
    int i, j, k, sum = 0;
    int min = INF;
    adjvec[0] = 0;
    lowcost[0] = 0;
    for(i = 1; i < nodes_count; ++i) {
        lowcost[i] = graph[0][i];
        adjvec[i] = 0;
    }
    for(j = 1; j < nodes_count; ++j) {
        min = INF;
        k = 0;
        for( i = 1; i < nodes_count; ++i) {
            if (lowcost[i] != 0 && lowcost[i] < min) {
                min = lowcost[i];
                k = i;
            }
        }
       sum += graph[adjvec[k]][k];
        for (i = 1; i < nodes_count; ++i) {
            if(lowcost[i] != 0 && graph[k][i] < lowcost[i]) {
                lowcost[i] = graph[k][i];
                adjvec[i] = k;
            }
        }
    }
    return sum;
}

int main()
{
    int type_num, i, j, sum;
    while ( 1 ) { 
        scanf("%d", &type_num);
        if (0 == type_num) 
            break;
        for(i = 0; i < type_num; ++i)
            scanf("%s", truck_type[i]);
    
        for(i = 0; i < type_num; ++i) {
            for(j = 0; j < type_num; ++j) {
                if(i == j) {
                    graph[i][j] = 0;
                    continue;
                }
                graph[i][j] = calcute_cost(truck_type[i], truck_type[j]);
            }
        }
        printf("The highest possible quality is 1/%d.\n",mini_span_tree_prim(graph, type_num));
    }
    return 0;
}
