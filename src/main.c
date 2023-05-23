#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/edge.h"
#include "../include/util.h"

int main(int argc, char *argv[])
{
  int node_amount = 0, edge_amount = 0, updates_amount = 0;
  int main_src_node = 0, main_dest_node = 0;

  char *input_file = strdup(argv[1]);

  // Getting output file name
  // char * output_file = strdup(argv[2]);

  FILE *file = fopen(input_file, "r");

  read_file_header(&node_amount, &edge_amount, &main_src_node, &main_dest_node, file);

  Edge *graph = read_edges(file, edge_amount);
  Update *updates = read_updates(file, &updates_amount);

  fclose(file);
  free(graph);
  free(updates);
  free(input_file);

  // Deallocating memory to output file name
  // free(output_file);
  return 0;
}
