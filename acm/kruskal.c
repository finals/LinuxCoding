#include <stdio.h>
#include <stdlib.h>

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

typedef struct {
    int begin;
    int end;
    int weight;
}Edge;

Edge edge_array[NUM*NUM];

int comp ( const void *a, const void *b )
{
    return (( Edge * ) a)->weight - (( Edge * ) b)->weight;
}

int init_edge_array(int graph[][NUM], int size)
{
    int i, j,k = 0;

    for(i = 0; i < size; ++i) {
        for(j = i; j < size; ++j) {
            if (graph[i][j] > 0 && graph[i][j] != INF) {
                edge_array[k].begin = i;
                edge_array[k].end = j;
                edge_array[k].weight = graph[i][j];
                k++;
            }
        }
    }
    qsort(edge_array, k, sizeof(Edge), comp);
 /*   for(i = 0; i < k; ++i) {
        printf("%d  %d  %d\n",edge_array[i].begin,edge_array[i].end,edge_array[i].weight);
    }
    printf("\n\n");
    */
    return k;
}

int Find(int parent[], int f)
{
    while(parent[f] > 0)
        f = parent[f];
    return f;
}

void min_span_tree_kruskal(int graph[][NUM], int size)
{
    int i, n, m;
    int parent[NUM];
    int k = init_edge_array(graph, size);

    for(i = 0; i < size; ++i) {
        parent[i] = 0;
    }

    for(i = 0; i < k; ++i) {
        n = Find(parent, edge_array[i].begin);
        m = Find(parent, edge_array[i].end);
        if(n != m) {
            parent[n] = m;
            printf("%d  %d  %d\n",edge_array[i].begin,edge_array[i].end,edge_array[i].weight);
        }
    }
}

int main()
{
    min_span_tree_kruskal(graph, NUM);
    return 0;
}






