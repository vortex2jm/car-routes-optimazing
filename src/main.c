#include "../include/edge.h"
#include "../include/util.h"
#include "../include/algorithm.h"
#include "../include/updates.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void calculate_path(AdjList **adjacency_vector, Update* velocity_updates, int node_amount, int edge_amount, int updates_amount, int main_src_node, 
                   int main_dest_node, int *path, double *total_time, double *total_distance, int *path_length);
char* format_time(double total_time);
void  write_output(FILE *out_file, double total_time, double total_distance, int* path, int path_length);


int main(int argc, char *argv[])
{
  int node_amount = 0, edge_amount = 0, updates_amount = 0;
  int main_src_node = 0, main_dest_node = 0;
  double intial_velocity;
  int path_length = 0;

  char *input_file = strdup(argv[1]);
  char *output_file = strdup(argv[2]);

  FILE *file = fopen(input_file, "r");

  read_file_header(&node_amount, &edge_amount, &main_src_node, &main_dest_node, &intial_velocity, file);
  AdjList **adjacency_vector = read_edges(file, node_amount, edge_amount, intial_velocity);
  Update *velocity_updates = read_updates(file, &updates_amount);

  // print_list_vector(adjacency_vector, node_amount);
  int *path = calloc((node_amount + 1), sizeof(int));

  double total_time = 0;
  double total_distance = 0;
  
  calculate_path(adjacency_vector, velocity_updates, node_amount, edge_amount, updates_amount, main_src_node, main_dest_node, path, &total_time, 
                &total_distance, &path_length);


  FILE *out_file = fopen(output_file, "w");
  write_output(out_file, total_time, total_distance, path, path_length);

  fclose(file);
  fclose(out_file);
  free(input_file);
  free(output_file);
  free(path);
  free(velocity_updates);
  end_list_vector(adjacency_vector, node_amount);
  return 0;
}


void calculate_path(AdjList **adjacency_vector, Update* velocity_updates, int node_amount, int edge_amount, int updates_amount, int main_src_node, 
                   int main_dest_node, int *path, double *total_time, double *total_distance, int *path_length)
{
  path[0] = main_src_node;
  double distanceTravelled = 0;
  double timeTravelled = 0;

  // Initializing temporary path (may change according to updates)
  int *temporary_path = calloc((node_amount + 1), sizeof(int));
  int temp_path_length = 0;

  int index_uptades = 0;
  // While there are uptades
  while(index_uptades < updates_amount)
  {
    dijkstra(adjacency_vector, node_amount, path[path_length[0]], main_dest_node, temporary_path, &distanceTravelled, &timeTravelled, edge_amount, &temp_path_length);

    double next_uptade_time = get_instant_time(velocity_updates[index_uptades]);

    int index_temporary_path = 1;
    while(next_uptade_time > total_time[0])
    {
      // Verify if the current node is the destination node;
      if(temporary_path[index_temporary_path - 1] == main_dest_node)
      {
        free(temporary_path);
        return;
      }
      // Get the distance and the time between the current node and the next one
      total_time[0] += get_time(find_adj_list(adjacency_vector[temporary_path[index_temporary_path - 1]-1], temporary_path[index_temporary_path]));
      total_distance[0] += get_distance(find_adj_list(adjacency_vector[temporary_path[index_temporary_path - 1]-1], temporary_path[index_temporary_path]));
      
      // Add node to the final path
      path[++path_length[0]] = temporary_path[index_temporary_path++];      
    }
    while(total_time[0] >= next_uptade_time)
    {
      update_adj(adjacency_vector[get_src_node(velocity_updates[index_uptades])-1], get_dest_node(velocity_updates[index_uptades]), 
                 get_new_velocity(velocity_updates[index_uptades]));
      
      index_uptades++;
      if(index_uptades == updates_amount) break;
      next_uptade_time = get_instant_time(velocity_updates[index_uptades]);
    }
  }

  // No updates left
  dijkstra(adjacency_vector, node_amount, path[path_length[0]], main_dest_node, temporary_path, &distanceTravelled, &timeTravelled, edge_amount, &temp_path_length);
  
  int index_temporary_path = 1;
  while(path[path_length[0]] != main_dest_node)
  {
    // Get the distance and the time between the current node and the next one
    total_time[0] += get_time(find_adj_list(adjacency_vector[temporary_path[index_temporary_path - 1]-1], temporary_path[index_temporary_path]));
    total_distance[0] += get_distance(find_adj_list(adjacency_vector[temporary_path[index_temporary_path - 1]-1], temporary_path[index_temporary_path]));

    // Add node to the final path
    path[++path_length[0]] = temporary_path[index_temporary_path++]; 
  }

  free(temporary_path);
}

void  write_output(FILE *out_file, double total_time, double total_distance, int* path, int path_length)
{
  char* string_total_time = format_time(total_time);
  total_distance = total_distance / 1000;
  int i = 0;
  for (i = 0; i < path_length; i++)
  {
    fprintf(out_file, "%d;", path[i]);
  }
  fprintf(out_file, "%d\n%f\n%s", path[i], total_distance, string_total_time);
  free(string_total_time);
}


char* format_time(double total_time)
{
  int hours = total_time / 3600;
  int minutes = ((int)total_time % 3600) / 60;
  double seconds = total_time - (hours * 3600) - (minutes * 60);
  char string_total_time[100];
  sprintf(string_total_time, "%02d:%02d:%f", hours, minutes, seconds);
  char* formated_time = strdup(string_total_time);
  return formated_time;
}