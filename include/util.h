#ifndef util_h
#define util_h
#include <stdio.h>
#include "edge.h"
#include "updates.h"

void read_file_header(int *node_amount, int *edge_amount, int *src_node, int *dest_node, FILE *file);

Edge *read_edges(FILE *file, int edge_amount);

Update *read_updates(FILE *file, int * updates_amount);

double calculate_weight(double distance, double velocity);

#endif
