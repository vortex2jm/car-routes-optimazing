#ifndef ITEM_H
#define ITEM_H

#include "edge.h"

typedef struct
{
  int id;
  Edge value;
} Item;

#define id(A) (A.id)                                   // return node identifier
#define value(A) (A.value)                             // return node value
#define more(A, B) (value(A).weight > value(B).weight) // compare two nodes values
#define exch(A, B) \
  {                \
    Item t = A;    \
    A = B;         \
    B = t;         \
  } // exchange two nodes

#endif
