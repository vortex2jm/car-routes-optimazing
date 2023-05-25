#include "../include/algorithm.h"
#include "../include/edge.h"
#include "../include/node.h"
#include "../include/PQ.h"

#define INFINITY 999999999

// Prototypes =============================================//
void dijkstra(Edge *graph, int node_amount, int edge_amount, int main_src_node, int main_dest_node);

// Implementations=========================================//
void dijkstra(Edge *graph, int node_amount, int edge_amount, int main_src_node, int main_dest_node)
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
    Node *pq;
    PQ_init(pq, node_amount);

    // Initializing source node
    dist[main_src_node] = 0;

    PQ_insert(pq, init_node(main_src_node, dist[main_src_node]));

    while (!PQ_empty(pq))
    {
        Node u = PQ_delmin(pq);
        if (visited[u.id] == 1)
            continue;

        visited[u.id] = 1;

        // For each neighbor of u
    }
}
