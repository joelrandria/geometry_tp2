#ifndef __VERTEX2F_H__
#define __VERTEX2F_H__

// Indices des coordonnées
#define X_COORD 0
#define Y_COORD 1

// Relations
#define VERTEX_LINK_TYPE_COUNT 1
#define VERTEX_RING_LINK 0

// Sens de navigation parmis les relations
#define VERTEX_BACKWARD_LINK 0
#define VERTEX_FORWARD_LINK 1

// Sens de rotation dans le plan
#define CLOCKWISE_DIRECTION -1
#define NO_DIRECTION 0
#define COUNTERCLOCKWISE_DIRECTION 1

// Ordres de comparaison de deux vertices
#define DESCENDING_VERTEX_ORDER -1
#define EQUAL_VERTICES 0
#define ASCENDING_VERTEX_ORDER 1

// Positionnement d'un objet par rapport à un autre objet
#define OUTSIDE_LOCATION -1
#define BORDER_LOCATION 0
#define INSIDE_LOCATION 1

/**
 * Définit une vertice à 2 dimensions possédant des liens vers d'autres vertices.
 */
typedef struct vertex2f
{
  // Coordonnées
  float coords[2];
  // Relations
  struct vertex2f* links[VERTEX_LINK_TYPE_COUNT][2];
} vertex2f;

vertex2f* new_vertex2f(float x, float y);
vertex2f* new_random_vertex2f(float x_max, float y_max);
int get_vertex2f_rotation_direction(vertex2f* a, vertex2f* b, vertex2f* p);
int is_vertex2f_on_edge(vertex2f* a, vertex2f* b, vertex2f* p);
int vertex2f_cmp_lex(vertex2f* a, vertex2f* b);

#endif
