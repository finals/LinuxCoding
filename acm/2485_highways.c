#include <stdio.h>

#define N 500
int graph[N][N];

typedef struct {
    int begin;
    int end;
    int weight;
}Edge;

Edge edge_array[N*N];

int comp ( const void *a, const void *b )
{
    return (( Edge * ) a)->weight - (( Edge * ) b)->weight;
}

int init_edge_array(int graph[][N], int size)
{
    int i, j,k = 0;

    for(i = 0; i < size; ++i) {
        for(j = i; j < size; ++j) {
            if (graph[i][j] > 0) {
                edge_array[k].begin = i;
                edge_array[k].end = j;
                edge_array[k].weight = graph[i][j];
                k++;
            }
        }
    }
    qsort(edge_array, k, sizeof(Edge), comp);

    return k;
}

int Find(int parent[], int f)
{
    while(parent[f] > 0)
        f = parent[f];
    return f;
}

int min_span_tree_kruskal(int graph[][N], int size)
{
    int i, n, m, max = 0;
    int parent[N];
    int k = init_edge_array(graph, size);

    for(i = 0; i < size; ++i) {
        parent[i] = 0;
    }

    for(i = 0; i < k; ++i) {
        n = Find(parent, edge_array[i].begin);
        m = Find(parent, edge_array[i].end);
        if(n != m) {
            parent[n] = m;
            if (edge_array[i].weight > max)
                max = edge_array[i].weight;
            //printf("%d  %d  %d\n",edge_array[i].begin,edge_array[i].end,edge_array[i].weight);
        }
    }
    return max;
}


/*
int min_span_tree_prim(int graph[N][N], int vil_nums)
{
    int i, j, k;
    int lowcost[N];
    int adjvec[N];
    int min;
    int max = 0;
    lowcost[0] = 0;
    adjvec[0] = 0;
    for(i = 1; i < vil_nums; ++i) {
        lowcost[i] = graph[0][i];
        adjvec[i] = 0;
    }

    for (j = 1; j < vil_nums; ++j) {
        min = 65537;
        for(i = 1; i < vil_nums; ++i) {
            if (lowcost[i] != 0 && lowcost[i] < min) {
                min = lowcost[i];
                k = i;
            }
        }
        if(lowcost[k] > max)
            max = lowcost[k];
        lowcost[k] = 0;
        for(i = 1; i < vil_nums; ++i) {
            if(lowcost[i] != 0 && graph[k][i] < lowcost[i]) {
                lowcost[i] = graph[k][i];
                adjvec[i] = k;
            }
        }     
    }
    return max;
}
*/

int main()
{
    int times, vil_nums;
    int i, j, t;
    scanf("%d", &times);

    for(t = 0; t < times; ++t) {
        scanf("%d", &vil_nums);
        for(i = 0; i < vil_nums; ++i) {
            for(j = 0;  j < vil_nums; ++j) {
                scanf("%d", &graph[i][j]);
            }
        }
        printf("%d\n", min_span_tree_kruskal(graph,vil_nums));
    }
    return 0;
}
