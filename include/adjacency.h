#ifndef adjacency_h
#define adjacency_h

#include <stdbool.h>

typedef struct priority_queue *PQ;

struct adj
{
    int node_id;
    double distance;
    double time;
};
typedef struct adj Adj;
Adj init_adj(int node_id, double distance, double time);
void print_adj(Adj adj);

//============================//
typedef struct adj_list AdjList;
typedef void (*ListCallback)(Adj, int, int *, double *, PQ);

AdjList *init_list();
void list_push(AdjList *list, Adj adj);
void list_traversal(AdjList *list, ListCallback callback, int v_id, int *visited, double *dist, PQ pq);
void end_list(AdjList *list);
void end_list_vector(AdjList **vector, int size);

#define id(A) (A.node_id)                   // return node identifier
#define value(A) (A.time)                   // return node value
#define greater(A, B) (value(A) > value(B)) // compare two nodes values
#define exch(A, B) \
    {              \
        Adj t = A; \
        A = B;     \
        B = t;     \
    } // exchange two nodes

#endif
