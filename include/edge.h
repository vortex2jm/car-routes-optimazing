#ifndef edge_h
#define edge_h

struct edge{
    int src;
    int dest;
    double distance;
    double weight;
};

typedef struct edge Edge;

Edge init_edge(int src, int dest, double distance, double weight);

void print_edge(Edge edge);

#endif
