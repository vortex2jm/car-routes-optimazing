#include "../include/edge.h"
#include "../include/util.h"
#include "../include/algorithm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

  // Testing adjacency list
  Update *velocity_updates = read_updates(file, &updates_amount);
  for (int x = 0; x < node_amount; x++)
  {
    // printf("NODE %d\n", x);
    // list_traversal(adjacency_vector[x], print_adj);
  }

  // Testing updates

  dijkstra(adjacency_vector, node_amount, main_src_node, main_dest_node);

  fclose(file);
  free(input_file);
  // free(output_file);
  free(velocity_updates);
  end_list_vector(adjacency_vector, node_amount);
  return 0;
}
