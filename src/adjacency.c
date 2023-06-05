#include "../include/adjacency.h"
#include <stdio.h>
#include <stdlib.h> 

Adj init_adj(int node_id, double distance){
    Adj adj;
    adj.node_id = node_id;
    adj.distance = distance;
    return adj;
}

void print_adj(Adj adj){
    printf("%d, %lf\n", adj.node_id, adj.distance);
}

//===============//
typedef struct cell Cell;
struct cell{
    Adj adj;
    Cell * next;
};

struct adj_list{
    Cell * first;
    Cell * last;
};

//========================//
AdjList * init_list(){
    AdjList * ad_list = malloc(sizeof(AdjList));
    ad_list->first = NULL;
    ad_list->last = NULL;
    return ad_list;
}

// You can  add parameters to this function too
void list_traversal(AdjList * list, ListCallback callback){
    
    if(!list)
        perror("Could not cross unexisting list!\n");

    Cell * current = list->first;
    while(current){
        // Define what callback gonna do
        callback(current->adj);
        current = current->next;
    }
}

void list_push(AdjList * list, Adj adj){

    if(!list)
        perror("Could not push item into unexisting list!\n");

    Cell * new_cell = malloc(sizeof(Cell));
    new_cell->next = NULL;
    new_cell->adj = adj;

    if(!list->first){
        list->first = new_cell;
        list->last = new_cell;
        return;
    }
    list->last->next = new_cell;
    list->last = new_cell;
}

void end_list(AdjList * list){
    if(list){
        Cell * current = list->first, *aux = NULL;
        while(current){
            aux = current->next;
            free(current);
            current = aux;
        }
        free(list);
    }
}

void end_list_vector(AdjList ** vector, int size){
    if(vector){
        printf("oi\n");
        for(int x=0; x<size; x++){
            end_list(vector[x]);
        }
        free(vector);
    }
}
