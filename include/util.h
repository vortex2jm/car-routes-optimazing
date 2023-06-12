#ifndef util_h
#define util_h
#include <stdio.h>
#include "updates.h"
#include "adjacency.h"

void read_file_header(int *node_amount, int *edge_amount, int *src_node, int *dest_node, double *velocity, FILE *file);

AdjList **read_edges(FILE *file, int node_amount, int edge_amount, double velocity);

Update *read_updates(FILE *file, int *updates_amount);

double calculate_weight(double distance, double velocity);

void calculate_path(AdjList **adjacency_vector, Update *velocity_updates, int node_amount, int edge_amount, int updates_amount, int main_src_node,
                    int main_dest_node, int *path, double *total_time, double *total_distance, int *path_length);

char *format_time(double total_time);

void write_output(FILE *out_file, double total_time, double total_distance, int *path, int path_length);

#endif
