#include <stdlib.h>
#include <time.h>

#include "triangle2f.h"

vertex2f** get_random_triangle2f(int x_max, int y_max)
{
  int i;
  vertex2f** vertices;

  srand(time(0));

  vertices = malloc(sizeof(vertex2f*) * 3);
  for (i = 0; i < 3; ++i)
    vertices[i] = new_random_vertex2f(x_max, y_max);

  while (get_vertex2f_rotation_direction(vertices[0], vertices[1], vertices[2]) == NO_DIRECTION)
  {
    free(vertices[0]);
    vertices[0] = new_random_vertex2f(x_max, y_max);
  }
  
  return (vertices);
}
int locate_vertex_triangle2f(vertex2f** triangle, vertex2f* p)
{
  int rotdir1;
  int rotdir2;
  int rotdir3;

  rotdir1 = get_vertex2f_rotation_direction(triangle[0], triangle[1], p);
  rotdir2 = get_vertex2f_rotation_direction(triangle[1], triangle[2], p);
  rotdir3 = get_vertex2f_rotation_direction(triangle[2], triangle[0], p);

  if ((rotdir1 == rotdir2) && (rotdir2 == rotdir3))
    return (INSIDE_LOCATION);

  if (is_vertex2f_on_edge(triangle[0], triangle[1], p))
    return (BORDER_LOCATION);
  if (is_vertex2f_on_edge(triangle[1], triangle[2], p))
    return (BORDER_LOCATION);
  if (is_vertex2f_on_edge(triangle[2], triangle[0], p))
    return (BORDER_LOCATION);

  return (OUTSIDE_LOCATION);
}
