#ifndef util_h
#define util_h
#include <stdio.h>
#include "edge.h"
#include "updates.h"
#include "adjacency.h"

void read_file_header(int *node_amount, int *edge_amount, int *src_node, int *dest_node, double *velocity, FILE *file);

// Depracated
// Edge *read_edges(FILE *file, int edge_amount);

AdjList **read_edges(FILE *file, int node_amount, int edge_amount, double velocity);

Update *read_updates(FILE *file, int *updates_amount);

double calculate_weight(double distance, double velocity);

#endif
