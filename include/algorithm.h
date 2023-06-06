#ifndef algorithm_h
#define algorithm_h

#include "adjacency.h"

/* Dijkstra's algorithm */
void dijkstra(AdjList **graph, int node_amount, int main_src_node, int main_dest_node, int *path, double *distance, double *time);

#endif /* algorithm_h */