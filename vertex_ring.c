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

void vertexring_length_(vertex_ring* r, void* args)
{
  ++*((int*)args);
}
int vertexring_length(vertex_ring* ring)
{
  int count;

  count = 0;
  vertexring_run(ring, vertexring_length_, &count, VR_FORWARD);

  return count;
}

void vertexring_last_(vertex_ring* r, void* args)
{
  *((vertex_ring**)args) = r;
}
vertex_ring* vertexring_last(vertex_ring* ring, int direction)
{
  vertex_ring* last;

  last = 0;
  vertexring_run(ring, vertexring_last_, &last, VR_FORWARD);

  return last;
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

void vertexring_print_(vertex_ring* r, void* args)
{
  printf("%d %d\r\n", (int)r->v->coords[0], (int)r->v->coords[1]);
}
void vertexring_print(vertex_ring* ring, int direction)
{
  vertexring_run(ring, vertexring_print_, 0, direction);
}

void vertexring_run(vertex_ring* ring, void(*func)(vertex_ring* r, void* args), void* args, int direction)
{
  vertex_ring* beginning;

  if (!ring)
    return;

  beginning = ring;

  func(ring, args);

  while (ring->siblings[direction] != beginning)
  {
    ring = ring->siblings[direction];

    func(ring, args);
  }
}

void vertexring_save_(vertex_ring* r, void* args)
{
  fprintf((FILE*)args, ", %f %f", r->v->coords[0], r->v->coords[1]);
}
void vertexring_save(vertex_ring* ring, const char* path)
{
  FILE* file;

  file = fopen(path, "w+");

  fprintf(file, "%d", vertexring_length(ring));

  vertexring_run(ring, vertexring_save_, file, VR_FORWARD);

  fprintf(file, "\r\n");

  fclose(file);
}
