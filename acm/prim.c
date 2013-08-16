#include <stdio.h>

#define INF 65535
#define NUM 9

int graph[NUM][NUM] =
{
	{0,10,INF,INF,INF,11,INF,INF,INF},
	{10,0,18,INF,INF,INF,16,INF,12},
	{INF,INF,0,22,INF,INF,INF,INF,8},
	{INF,INF,22,0,20,INF,24,16,21},
	{INF,INF,INF,20,0,26,INF,7,INF},
	{11,INF,INF,INF,26,0,17,INF,INF},
	{INF,16,INF,24,INF,17,0,19,INF},
	{INF,INF,INF,16,7,INF,19,0,INF},
	{INF,12,8,21,INF,INF,INF,INF,0}
};


void print_array(int arr[], int len)
{
    int i;
    for(i = 0; i < len; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}


void MiniSpanTree_Prim(int graph[][NUM], int nodes_num)
{
    int min, i, j, k;
    int lowcost[NUM];
    int adjvec[NUM];
    
    lowcost[0] = 0;
    adjvec[0] = 0;
    for (i = 1; i < NUM; ++i) {
        lowcost[i] = graph[0][i];
 	adjvec[i] = 0;
    }

    for(j = 1; j < NUM; ++j) {
        min = INF;
	 k = 0;
	 for (i = 1; i < NUM; ++i) {
		if (lowcost[i] != 0 && lowcost[i] < min) {
		    min = lowcost[i];			
                   k = i;
		}
	}
	printf("(%d, %d)\n", adjvec[k], k);		
       lowcost[k] = 0;
	for (i = 1; i < NUM; ++i) {
	    if(graph[k][i] < lowcost[i]) {
	        lowcost[i] = graph[k][i];
		adjvec[i] = k;		
            }
	}
    }
    print_array(lowcost, NUM);
}

int main()
{
    MiniSpanTree_Prim(graph, NUM);
    return 0;
}

