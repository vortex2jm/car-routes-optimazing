#include <stdio.h>
#include <stdlib.h>
#include "../include/updates.h"

Update init_update(int src_node, int dest_node, double instant_time, double new_velocity){
    Update up;
    up.src_node = src_node;
    up.dest_node = dest_node;
    up.instant_time = instant_time;
    up.new_velocity = new_velocity;
    return up;
}

// Auxiliar function
void print_update(Update update){
    printf("%.0lf;%d;%d;%.0lf\n", update.instant_time, update.src_node, update.dest_node, update.new_velocity);
}
