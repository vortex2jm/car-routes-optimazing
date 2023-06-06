#include "../include/algorithm.h"
#include "../include/edge.h"
#include "../include/adjacency.h"
#include "../include/PQ.h"
#include <stdlib.h>
#include <stdio.h>

#define INFINITY 999999999

// Prototypes =============================================//
void dijkstra(AdjList **graph, int node_amount, int main_src_node, int main_dest_node);
void updateDistanceCallback(Adj adj, int v_id, int *visited, double *dist, PQ pq);

// Implementations=========================================//
void dijkstra(AdjList **graph, int node_amount, int main_src_node, int main_dest_node)
{
    double dist[node_amount];
    int visited[node_amount];

    // Initializing dist and visited

    for (int i = 0; i < node_amount; i++)
    {
        dist[i] = INFINITY;
        visited[i] = 0;
    }

    // Initializing priority queue
    PQ pq = malloc(sizeof(struct priority_queue));
    PQ_init(pq, node_amount);
    // Setting main source node distance to 0

    dist[main_src_node] = 0;
    PQ_insert(pq, init_adj(main_src_node, 0, 0));

    // Dijkstra's algorithm

    while (pq->N != 0)
    {
        Adj v = PQ_delmin(pq);
        int v_id = id(v);
        visited[v_id] = 1;

        AdjList *list = graph[v_id];

        list_traversal(list, updateDistanceCallback, v_id, visited, dist, pq);
    }

    // Printing results

    printf("Dijkstra's algorithm results:\n");
    printf("Source node: %d\n", main_src_node);
    printf("Destination node: %d\n", main_dest_node);
    printf("Distance: %lf\n", dist[main_dest_node]);
    printf("=====================================\n");
}

void updateDistanceCallback(Adj adj, int v_id, int *visited, double *dist, PQ pq)
{
    int w_id = id(adj);
    if (visited[w_id] == 0)
    {
        if (dist[w_id] > dist[v_id] + value(adj))
        {
            dist[w_id] = dist[v_id] + value(adj);
            PQ_insert(pq, init_adj(w_id, dist[w_id], 0));
        }
    }
}
