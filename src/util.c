#include <stdio.h>
#include <stdlib.h>
#include "../include/util.h"
#include "../include/edge.h"

// Prototypes =============================================//
void read_file_header(int *node_amount, int *edge_amount, int *src_node, int *dest_node, FILE *file);
double calculate_weight(double distance, double velocity);
Edge *read_edges(FILE *file, int edge_amount);

// Implementations=========================================//
void read_file_header(int *node_amount, int *edge_amount, int *src_node, int *dest_node, FILE *file)
{
    fscanf(file, "%d;%d\n%d;%d\n", node_amount, edge_amount, src_node, dest_node);
}

Edge *read_edges(FILE *file, int edge_amount)
{
    // Reading velocity
    double velocity = 0.0;
    fscanf(file, "%lf\n", &velocity);

    Edge *edge_vector = malloc(sizeof(Edge) * edge_amount);
    int src, dest;
    double distance, weight;

    for (int x = 0; x < edge_amount; x++)
    {
        fscanf(file, "%d;%d;%lf\n", &src, &dest, &distance);
        weight = calculate_weight(distance, velocity); // weight = time
        edge_vector[x] = init_edge(src, dest, distance, weight);
    }
    return edge_vector;
}

Update *read_updates(FILE *file, int * updates_amount)
{
    // Getting current seek
    long file_seek = ftell(file);

    // Counting number of updates to allocate memory
    int line_count = 0;
    char aux[50];
    while (!feof(file))
    {
        fscanf(file, "%[^\n]\n", aux);
        line_count++;
    }

    // Assigning value of updates amount
    *updates_amount = line_count;
    
    // Reseting seek after counting
    fseek(file, file_seek, SEEK_SET);

    // Reading updates
    Update *updates = malloc(sizeof(Update) * line_count);
    int src_node, dest_node;
    double instant_time, new_velocity;
    int i = 0;
    while (!feof(file))
    {
        fscanf(file, "%lf;%d;%d;%lf\n", &instant_time, &src_node, &dest_node, &new_velocity);
        updates[i] = init_update(src_node, dest_node, instant_time, new_velocity);
        i++;
    }
    return updates;
}

double calculate_weight(double distance, double velocity)
{
    // Transforming velocity to m/s
    // Returning time in seconds
    velocity = velocity / 3.6;
    return velocity / distance;
}
