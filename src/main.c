#include "../include/edge.h"
#include "../include/util.h"
#include "../include/algorithm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void printPathMain(int *path, int node);

int main(int argc, char *argv[])
{
  int node_amount = 0, edge_amount = 0, updates_amount = 0;
  int main_src_node = 0, main_dest_node = 0;
  double intial_velocity;

  char *input_file = strdup(argv[1]);
  // char * output_file = strdup(argv[2]);

  FILE *file = fopen(input_file, "r");

  read_file_header(&node_amount, &edge_amount, &main_src_node, &main_dest_node, &intial_velocity, file);
  AdjList **adjacency_vector = read_edges(file, node_amount, edge_amount, intial_velocity);
  Update *velocity_updates = read_updates(file, &updates_amount);

  int *path = malloc(sizeof(int) * (node_amount + 1));
  for (int i = 0; i < node_amount; i++)
    path[i] = 0;
  double distanceTravelled = 0;
  double timeTravelled = 0;

  dijkstra(adjacency_vector, node_amount, main_src_node, main_dest_node, path, &distanceTravelled, &timeTravelled);

  printf("Distance: %lf\n", distanceTravelled);
  printf("Time: %lf\n", timeTravelled);
  printf("Path: ");
  printPath(path, main_dest_node);
  printf("\n");

  fclose(file);
  free(input_file);
  // free(output_file);
  free(path);
  free(velocity_updates);
  end_list_vector(adjacency_vector, node_amount);
  return 0;
}

// void printPathMain(int *path, int node)
// {
//   if (path[node] == 0)
//   {
//     printf("%d", node);
//   }
//   else
//   {
//     printPath(path, path[node]);
//     printf(" -> %d", node);
//   }
// }
