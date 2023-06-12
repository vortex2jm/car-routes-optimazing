#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/util.h"
#include "../include/algorithm.h"

// Implementations=========================================//
void read_file_header(int *node_amount, int *edge_amount, int *src_node, int *dest_node, double *velocity, FILE *file)
{
    fscanf(file, "%d;%d\n%d;%d\n%lf\n", node_amount, edge_amount, src_node, dest_node, velocity);
}

// Reading edges and creating adjacency vector
//======================================================//
AdjList **read_edges(FILE *file, int node_amount, int edge_amount, double velocity)
{

    AdjList **list_vector = malloc(sizeof(AdjList *) * node_amount);
    for (int x = 0; x < node_amount; x++)
    {
        list_vector[x] = init_list();
    }

    Adj adj;
    int src, dest;
    double distance, weight;

    for (int x = 0; x < edge_amount; x++)
    {
        fscanf(file, "%d;%d;%lf\n", &src, &dest, &distance);
        adj = init_adj(dest, distance, calculate_weight(distance, velocity));
        list_push(list_vector[src - 1], adj);
    }

    return list_vector;
}

//======================================================//
Update *read_updates(FILE *file, int *updates_amount)
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
    return distance / velocity;
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
