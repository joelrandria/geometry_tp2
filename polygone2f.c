#include <stdio.h>

#include "polygone2f.h"

vertex2f* get_polygone2f_min_lex(vertex2f* polygone)
{
  vertex2f* min;
  vertex2f* beginning;

  min = polygone;
  beginning = polygone;
  while (polygone->links[VERTEX_RING_LINK][VERTEX_FORWARD_LINK] != beginning)
  {
    if (vertex2f_cmp_lex(min, polygone) == DESCENDING_VERTEX_ORDER)
      min = polygone;
    polygone = polygone->links[VERTEX_RING_LINK][VERTEX_FORWARD_LINK];
  }

  return (min);
}
int get_polygone2f_rotation_direction(vertex2f* polygone)
{
  vertex2f* min;
  vertex2f* prev;
  vertex2f* next;

  min = get_polygone2f_min_lex(polygone);
  prev = min->links[VERTEX_RING_LINK][VERTEX_BACKWARD_LINK];
  next = min->links[VERTEX_RING_LINK][VERTEX_FORWARD_LINK];

  return (get_vertex2f_rotation_direction(prev, min, next));
}
rect2f* get_polygone2f_bounding_rect(vertex2f* polygone)
{
  float x_min;
  float y_min;
  float x_max;
  float y_max;
  rect2f* rect;
  vertex2f* beginning;

  beginning = polygone;
  x_min = x_max = polygone->coords[X_COORD];
  y_min = y_max = polygone->coords[Y_COORD];
  while (polygone->links[VERTEX_RING_LINK][VERTEX_FORWARD_LINK] != beginning)
  {
    if (polygone->coords[X_COORD] < x_min)
      x_min = polygone->coords[X_COORD];
    else if (polygone->coords[X_COORD] > x_max)
      x_max = polygone->coords[X_COORD];
    if (polygone->coords[Y_COORD] < y_min)
      y_min = polygone->coords[Y_COORD];
    else if (polygone->coords[Y_COORD] > y_max)
      y_max = polygone->coords[Y_COORD];

    polygone = polygone->links[VERTEX_RING_LINK][VERTEX_FORWARD_LINK];
  }

  rect = new_rect2f();
  rect->down_left = new_vertex2f(x_min, y_min);
  rect->down_right = new_vertex2f(x_max, y_min);
  rect->up_right = new_vertex2f(x_max, y_max);
  rect->up_left = new_vertex2f(x_min, y_max);

  return (rect);
}
int locate_vertex_polygone2f(vertex2f* polygone, vertex2f* p)
{
  int point_location;
  int ccw_browsing_direction;
  vertex2f* beginning;
  vertex2f* current_triangle[3];
  int current_triangle_rotdir;

  switch (get_polygone2f_rotation_direction(polygone))
  {
  case CLOCKWISE_DIRECTION: ccw_browsing_direction = VERTEX_BACKWARD_LINK; break;
  default: ccw_browsing_direction = VERTEX_FORWARD_LINK;
  }

  beginning = polygone;
  point_location = OUTSIDE_LOCATION;
  while (polygone->links[VERTEX_RING_LINK][ccw_browsing_direction] != beginning)
  {
    current_triangle[0] = polygone;
    current_triangle[1] = current_triangle[0]->links[VERTEX_RING_LINK][ccw_browsing_direction];
    current_triangle[2] = current_triangle[1]->links[VERTEX_RING_LINK][ccw_browsing_direction];

    current_triangle_rotdir = get_vertex2f_rotation_direction(current_triangle[0],
							      current_triangle[1],
							      current_triangle[2]);

    /* if () */

    polygone = polygone->links[VERTEX_RING_LINK][ccw_browsing_direction];
  }

  return (point_location);
}
