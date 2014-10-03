#ifndef __VERTEX2F_RING_H__
#define __VERTEX2F_RING_H__

#include "vertex2f.h"

void print_vertex2f_ring(vertex2f* ring, int direction);
vertex2f* insert_vertex2f_in_ring(vertex2f* ring, vertex2f* vertex, int position);

#endif
