#ifndef TRIANGLE2F_H
#define TRIANGLE2F_H

#include "vertex2f.h"

vertex2f** get_random_triangle2f(int x_max, int y_max);
int locate_vertex_triangle2f(vertex2f** triangle, vertex2f* p);

#endif
