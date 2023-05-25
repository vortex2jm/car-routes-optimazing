#ifndef edge_h
#define edge_h
/*
This approach was chosen to avoid pointer access
which would be the case with incomplete types
*/

// Don`t need getters and setters for structs
// Get and Set properties with "." operator
struct edge
{
    int src;
    int dest;
    double distance;
    double weight;
};

typedef struct edge Edge;

// Use this function to create a new structure. It will be returned by copy
Edge init_edge(int src, int dest, double distance, double weight);

// Auxiliar function
void print_edge(Edge edge);

#endif
