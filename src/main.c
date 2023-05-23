#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/edge.h"
#include "../include/util.h"

int main(int argc, char *argv[])
{
  int node_amount=0, edge_amount=0;
  int src_node=0, dest_node=0;

  char * input_file = strdup(argv[1]);
  // char * output_file = strdup(argv[2]);

  FILE * file = fopen(input_file, "r");

  read_file_header(&node_amount, &edge_amount, &src_node, &dest_node, file);
  Edge * graph = read_edges(file, edge_amount);
  
  for(int x=0; x<edge_amount; x++){
    print_edge(graph[x]);
  }
  
  free(graph);
  fclose(file);
  free(input_file);
  // free(output_file);

  return 0;
}
