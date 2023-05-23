#ifndef util_h
#define util_h
#include <stdio.h>
#include "edge.h"

void read_file_header(int * node_amount, int * edge_amount, int * src_node, int * dest_node, FILE * file);

Edge * read_edges(FILE * file, int edges_amount);

double calculate_weight(double distance, double velocity);

#endif
