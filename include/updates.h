#ifndef updates_h
#define updates_h
/*
This approach was chosen to avoid pointer access
which would be the case with incomplete types
*/ 

// Don`t need getters and setters for structs
// Get and Set properties with "." operator
struct update{
    int src_node;
    int dest_node;
    double instant_time;
    double new_velocity;
};

typedef struct update Update;

// Use this function to create a new structure. It will be returned by copy
Update init_update(int src_node, int dest_node, double instant_time, double new_velocity);

// Auxiliar function
void print_update(Update update);

#endif
