#include <stdio.h>
#include <stdlib.h>
#include "../include/edge.h"

Edge init_edge(int src, int dest, double distance, double weight)
{
    Edge edge;
    edge.src = src;
    edge.dest = dest;
    edge.distance = distance;
    edge.weight = weight; // Using weight instead velocity
    return edge;
}

// Auxiliar function
void print_edge(Edge edge)
{
    printf("%d;%d;%.2lf;%.0lf\n", edge.src, edge.dest, edge.distance, edge.weight);
}
