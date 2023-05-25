#include "../include/node.h"

Node init_node(int id, int value)
{
    Node node;
    node.id = id;
    node.value = value;
    return node;
}