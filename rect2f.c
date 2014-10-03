#include <stdlib.h>

#include "rect2f.h"

rect2f* new_rect2f()
{
  rect2f* rect = malloc(sizeof(rect2f));

  rect->down_left = new_vertex2f(0, 0);
  rect->down_right = new_vertex2f(0, 0);
  rect->up_right = new_vertex2f(0, 0);
  rect->up_left = new_vertex2f(0, 0);

  return (rect);
}
float get_rect2f_width(rect2f* rect)
{
  return (rect->down_right->coords[X_COORD] - rect->down_left->coords[X_COORD]);
}
float get_rect2f_height(rect2f* rect)
{
  return (rect->up_right->coords[Y_COORD] - rect->down_right->coords[Y_COORD]);
}
