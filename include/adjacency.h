#ifndef adjacency_h
#define adjacency_h

struct adj {
    int node_id;
    double distance;
}; 
typedef struct adj Adj;
Adj init_adj(int node_id, double distance);
void print_adj(Adj adj);

//============================//
typedef struct adj_list AdjList;
typedef void(*ListCallback)(Adj);

AdjList * init_list();
void list_push(AdjList * list, Adj adj);
void list_traversal(AdjList * list, ListCallback callback);
void end_list(AdjList * list);
void end_list_vector(AdjList ** vector, int size);

#endif
