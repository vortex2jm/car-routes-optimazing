#include "../include/algorithm.h"
#include "../include/edge.h"
#include "../include/adjacency.h"
#include "../include/PQ.h"
#include "../include/util.h"
#include <stdlib.h>
#include <stdio.h>

#define INFINITY 999999999

// Prototypes =============================================//
void dijkstra(AdjList **graph, int node_amount, int main_src_node, int main_dest_node, int *path, double *distanceTraveled, double *timeTraveled);
void updateDistanceCallback(Adj adj, int v_id, int *visited, double *dist, double *time, PQ pq, int *path);
void printPath(int *path, int node);

// Implementations=========================================//
void dijkstra(AdjList **graph, int node_amount, int main_src_node, int main_dest_node, int *path, double *distanceTraveled, double *timeTraveled)
{
    double time[node_amount + 1];
    double dist[node_amount + 1];
    int visited[node_amount + 1];

    // Initializing dist and visited

    for (int i = 1; i <= node_amount; i++)
    {
        dist[i] = INFINITY;
        path[i] = 0;
        visited[i] = 0;
        time[i] = INFINITY;
    }

    // Initializing priority queue
    PQ pq = malloc(sizeof(struct priority_queue));
    PQ_init(pq, node_amount);
    // Setting main source node distance to 0

    dist[main_src_node] = 0;
    time[main_src_node] = 0;
    PQ_insert(pq, init_adj(main_src_node, 0, 0));

    // Dijkstra's algorithm

    while (pq->N != 0)
    {
        Adj v = PQ_delmin(pq);
        int v_id = id(v);
        visited[v_id] = 1;

        AdjList *list = graph[v_id - 1];
        list_traversal(list, updateDistanceCallback, v_id, visited, dist, time, pq, path);
    }

    // Printing path
    // printf("Path: ");
    // printPath(path, main_dest_node);
    // printf("\n");

    // Printing results
    // printf("Dijkstra's algorithm results:\n");
    // printf("Source node: %d\n", main_src_node);
    // printf("Destination node: %d\n", main_dest_node);
    // printf("Distance: %lf\n", dist[main_dest_node]);
    // printf("Time: %lf\n", time[main_dest_node]);
    // printf("=====================================\n");

    // Saving results

    distanceTraveled[0] = dist[main_dest_node];
    timeTraveled[0] = time[main_dest_node];
    printf("Dijkstra's algorithm results:\n");

    PQ_finish(pq);
    free(pq);
}

void updateDistanceCallback(Adj adj, int v_id, int *visited, double *dist, double *time, PQ pq, int *path)
{
    int w_id = id(adj);
    if (visited[w_id] == 0)
    {
        if (time[w_id] > time[v_id] + value(adj))
        {
            time[w_id] = time[v_id] + value(adj);
            dist[w_id] = dist[v_id] + dist(adj);
            path[w_id] = v_id;
            PQ_insert(pq, init_adj(w_id, dist[w_id], time[w_id]));
        }
    }
}

void printPath(int *path, int node)
{
    if (path[node] == 0)
    {
        printf("%d", node);
    }
    else
    {
        printPath(path, path[node]);
        printf(" -> %d", node);
    }
}
