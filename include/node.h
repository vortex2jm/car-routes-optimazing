#ifndef NODE_H
#define NODE_H

typedef struct
{
  int id;
  int value;
} Node;

#define id(A) (A.id)                     // return node identifier
#define value(A) (A.value)               // return node value
#define greater(A, B) (value(A) > value(B)) // compare two nodes values
#define exch(A, B) \
  {                \
    Node t = A;    \
    A = B;         \
    B = t;         \
  } // exchange two nodes

Node init_node(int id, int value);

#endif
