#include <stdio.h>
#include <stdlib.h>
#include "../include/util.h"
#include "../include/edge.h"

double calculate_weight(double distance, double velocity);
Edge *read_edges(FILE *file, int edge_amount);

void read_file_header(int *node_amount, int *edge_amount, int *src_node, int *dest_node, FILE *file){
    fscanf(file, "%d;%d\n%d;%d\n", node_amount, edge_amount, src_node, dest_node);
}

Edge *read_edges(FILE *file, int edge_amount)
{   
    double velocity = 0.0;
    fscanf(file, "%lf\n", &velocity);

    Edge * edge_vector = malloc(sizeof(Edge)*edge_amount);
    int src, dest;
    double distance, weight;

    for(int x=0; x<edge_amount; x++){
        fscanf(file, "%d;%d;%lf\n", &src, &dest, &distance);
        weight = calculate_weight(distance, velocity);
        edge_vector[x] = init_edge(src, dest, distance, weight);
    }    
    return edge_vector;
}

double calculate_weight(double distance, double velocity){
    // Transforming to m/s to return time in seconds
    velocity = velocity/3.6;
    return velocity / distance;
}
