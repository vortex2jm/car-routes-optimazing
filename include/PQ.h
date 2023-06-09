#ifndef PQ_H
#define PQ_H

#include <stdbool.h>
#include "adjacency.h"

struct priority_queue
{
    Adj *pq;
    int N;
    int *map;
};

typedef struct priority_queue *PQ;

void PQ_init(PQ pq, int maxN);                     // cria uma min PQ com capacidade maxN
void PQ_insert(PQ pq, Adj edge);                   // Insere Adj na PQ. A maior prioridade é a do Adj com menor campo 'value'
Adj PQ_delmin(PQ pq);                              // Remove Adj com menor campo 'value' da PQ
void PQ_decrease_key(PQ pq, int id, double value); // Muda a prioridade do nó com identificador 'id' para 'value'
Adj PQ_min(PQ pq);                                 // Retorna Adj com menor campo 'value' da PQ
bool PQ_empty(PQ pq);                              // Retorna True se a PQ não tem elementos
int PQ_size(PQ pq);                                // Número de elementos na PQ
void PQ_finish(PQ pq);                             // Libera memória

#endif
