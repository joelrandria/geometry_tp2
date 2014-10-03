#include <stdlib.h>

#include "vertex2f.h"

vertex2f* new_vertex2f(float x, float y)
{
  int i;
  vertex2f* vertex;

  vertex = malloc(sizeof(vertex2f));

  vertex->coords[X_COORD] = x;
  vertex->coords[Y_COORD] = y;

  for (i = 0; i < VERTEX_LINK_TYPE_COUNT; ++i)
  {
    vertex->links[i][VERTEX_BACKWARD_LINK] = 0;
    vertex->links[i][VERTEX_FORWARD_LINK] = 0;
  }

  vertex->links[VERTEX_RING_LINK][VERTEX_BACKWARD_LINK] = vertex;
  vertex->links[VERTEX_RING_LINK][VERTEX_FORWARD_LINK] = vertex;

  return (vertex);
}
vertex2f* new_random_vertex2f(float x_max, float y_max)
{
  vertex2f* vertex;

  vertex = new_vertex2f(0, 0);

  vertex->coords[X_COORD] = rand() % (int)x_max;
  vertex->coords[Y_COORD] = rand() % (int)y_max;

  return (vertex);
}
int get_vertex2f_rotation_direction(vertex2f* a, vertex2f* b, vertex2f* c)
{
  float cross_product_zval;

  cross_product_zval = (b->coords[X_COORD] - a->coords[X_COORD]) * (c->coords[Y_COORD] - a->coords[Y_COORD])
    - (c->coords[X_COORD] - a->coords[X_COORD]) * (b->coords[Y_COORD] - a->coords[Y_COORD]);

  if (cross_product_zval < 0)
    return (CLOCKWISE_DIRECTION);
  if (cross_product_zval > 0)
    return (COUNTERCLOCKWISE_DIRECTION);
  return (NO_DIRECTION);
}
int is_in_range(float bound1, float bound2, float val)
{
  float temp;

  if (bound1 > bound2)
  {
    temp = bound1;
    bound1 = bound2;
    bound2 = temp;
  }

  return ((bound1 <= val) && (val <= bound2));
}
int is_vertex2f_on_edge(vertex2f* a, vertex2f* b, vertex2f* c)
{
  if (get_vertex2f_rotation_direction(a, b, c) == NO_DIRECTION)
    return (is_in_range(a->coords[X_COORD], b->coords[X_COORD], c->coords[X_COORD])
	    && is_in_range(a->coords[Y_COORD], b->coords[Y_COORD], c->coords[Y_COORD]));
  return (0);
}
int vertex2f_cmp_lex(vertex2f* a, vertex2f* b)
{
  if (a->coords[X_COORD] < b->coords[X_COORD])
    return (ASCENDING_VERTEX_ORDER);
  if (a->coords[X_COORD] == b->coords[X_COORD])
  {
    if (a->coords[Y_COORD] < b->coords[Y_COORD])
      return (ASCENDING_VERTEX_ORDER);
    if (a->coords[Y_COORD] == b->coords[Y_COORD])
      return (EQUAL_VERTICES);
  }
  return (DESCENDING_VERTEX_ORDER);
}
