#include <stdio.h>

#include "vertex2f.h"
#include "vertex2f_ring.h"

void print_vertex2f_ring(vertex2f* ring, int direction)
{
  vertex2f* beginning;

  if (!ring)
  {
    printf("\r\n");
    return;
  }

  beginning = ring;
  while (ring->links[VERTEX_RING_LINK][direction] != beginning)
  {
    printf("(%d,%d)\r\n", (int)ring->coords[X_COORD], (int)ring->coords[Y_COORD]);
    ring = ring->links[VERTEX_RING_LINK][direction];
  }
  printf("(%d,%d)\r\n", (int)ring->coords[X_COORD], (int)ring->coords[Y_COORD]);
}
vertex2f* insert_vertex2f_in_ring(vertex2f* ring, vertex2f* vertex, int position)
{
  vertex2f* temp;

  if (!ring)
    return (vertex);

  temp = ring->links[VERTEX_RING_LINK][position];

  ring->links[VERTEX_RING_LINK][position] = vertex;

  vertex->links[VERTEX_RING_LINK][position] = temp;
  temp->links[VERTEX_RING_LINK][!position] = vertex;

  vertex->links[VERTEX_RING_LINK][!position] = ring;

  return (vertex);
}
