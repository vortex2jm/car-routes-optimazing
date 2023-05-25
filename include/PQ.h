#ifndef PQ_H
#define PQ_H

#include <stdbool.h>
#include "node.h"

void PQ_init(Node *pq, int maxN);                     // cria uma min PQ com capacidade maxN
void PQ_insert(Node *pq, Node edge);                  // Insere Node na PQ. A maior prioridade é a do Node com menor campo 'value'
Node PQ_delmin();                                     // Remove Node com menor campo 'value' da PQ
void PQ_decrease_key(Node *pq, int id, double value); // Muda a prioridade do nó com identificador 'id' para 'value'
Node PQ_min();                                        // Retorna Node com menor campo 'value' da PQ
bool PQ_empty();                                      // Retorna True se a PQ não tem elementos
int PQ_size();                                        // Número de elementos na PQ
void PQ_finish();                                     // Libera memória

#endif
