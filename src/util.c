#include <stdio.h>
#include <stdlib.h>
#include "../include/util.h"

// Implementations=========================================//
void read_file_header(int *node_amount, int *edge_amount, int *src_node, int *dest_node, double *velocity, FILE *file)
{
    fscanf(file, "%d;%d\n%d;%d\n%lf\n", node_amount, edge_amount, src_node, dest_node, velocity);
}

// Depracated
//======================================================//
// Edge *read_edges(FILE *file, int edge_amount)
// {
//     // Reading velocity
//     double velocity = 0.0;
//     fscanf(file, "%lf\n", &velocity);

//     Edge *edge_vector = malloc(sizeof(Edge) * edge_amount);
//     int src, dest;
//     double distance, weight;

//     for (int x = 0; x < edge_amount; x++)
//     {
//         fscanf(file, "%d;%d;%lf\n", &src, &dest, &distance);
//         weight = calculate_weight(distance, velocity); // weight = time
//         edge_vector[x] = init_edge(src, dest, distance, weight);
//     }
//     return edge_vector;
// }

// Reading edges and creating adjacency vector
//======================================================//
AdjList ** read_edges(FILE * file, int node_amount, int edge_amount){

    AdjList ** list_vector = malloc(sizeof(AdjList*) * node_amount);
    for(int x=0; x<node_amount; x++){
        list_vector[x] = init_list();
    }

    Adj adj;
    int src, dest;
    double distance, weight;

    for (int x = 0; x < edge_amount; x++)
    {
        fscanf(file, "%d;%d;%lf\n", &src, &dest, &distance);
        adj = init_adj(dest, distance);
        list_push(list_vector[src-1], adj);
    }

    return list_vector;
}

//======================================================//
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

//======================================================//
double calculate_weight(double distance, double velocity)
{
    // Transforming velocity to m/s
    // Returning time in seconds
    velocity = velocity / 3.6;
    return velocity / distance;
}
