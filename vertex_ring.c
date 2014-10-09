#include <stdio.h>
#include <stdlib.h>

#include "vertex_ring.h"

vertex_ring* vertexring_create(vertex* v)
{
  vertex_ring* item;

  item = malloc(sizeof(vertex_ring));
  item->v = v;
  item->siblings[VR_BACKWARD] = item;
  item->siblings[VR_FORWARD] = item;

  return item;
}

vertex_ring* vertexring_last(vertex_ring* ring, int direction)
{
  vertex_ring* beginning;

  if (!ring)
    return 0;

  beginning = ring;
  while (ring->siblings[direction] != beginning)
    ring = ring->siblings[direction];

  return ring;
}
vertex* vertexring_findbycoord(vertex_ring* ring, float x, float y, float epsilon)
{
  vertex ref;
  vertex_ring* beginning;

  if (!ring)
    return 0;

  ref.coords[0] = x;
  ref.coords[1] = y;

  if (vertex_distance(ring->v, &ref) < epsilon)
    return (ring->v);

  beginning = ring;
  while (ring->siblings[VR_FORWARD] != beginning)
  {
    ring = ring->siblings[VR_FORWARD];

    if (vertex_distance(ring->v, &ref) < epsilon)
      return (ring->v);
  }

  return 0;
}

vertex_ring* vertexring_add(vertex_ring* ring, vertex* v, int direction)
{
  vertex_ring* temp;
  vertex_ring* new_item;

  new_item = vertexring_create(v);

  if (!ring)
    return new_item;

  temp = ring->siblings[direction];

  ring->siblings[direction] = new_item;

  new_item->siblings[direction] = temp;
  temp->siblings[!direction] = new_item;

  new_item->siblings[!direction] = ring;

  return new_item;
}
vertex_ring* vertexring_enqueue(vertex_ring* ring, vertex* v, int direction)
{
  vertex_ring* last;

  last = vertexring_last(ring, direction);
  if (!last)
    return vertexring_create(v);

  vertexring_add(last, v, direction);

  return ring;
}

void vertexring_printvertex(vertex* v)
{
  printf("%d %d\r\n", (int)v->coords[0], (int)v->coords[1]);
}
void vertexring_print(vertex_ring* ring, int direction)
{
  vertexring_run(ring, vertexring_printvertex, direction);
}

void vertexring_run(vertex_ring* ring, void(*func)(vertex* v), int direction)
{
  vertex_ring* beginning;

  if (!ring)
    return;

  beginning = ring;

  func(ring->v);

  while (ring->siblings[direction] != beginning)
  {
    ring = ring->siblings[direction];

    func(ring->v);
  }
}
