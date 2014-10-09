#ifndef __VERTEX_RING_H__
#define __VERTEX_RING_H__

#include "vertex.h"

// Sens de navigation dans l'anneau
#define VR_BACKWARD 0
#define VR_FORWARD 1

typedef struct _vertex_ring
{
  vertex* v;
  struct _vertex_ring* siblings[2];
} vertex_ring;

// Création, insertion, ...
vertex_ring* vertexring_create(vertex* v);
vertex_ring* vertexring_add(vertex_ring* ring, vertex* v, int direction);
vertex_ring* vertexring_enqueue(vertex_ring* ring, vertex* v, int direction);

// Propriétés basiques
int vertexring_length(vertex_ring* ring);

// Accès aux éléments
vertex_ring* vertexring_last(vertex_ring* ring, int direction);
vertex* vertexring_findbycoord(vertex_ring* ring, float x, float y, float epsilon);

// Affichage
void vertexring_print(vertex_ring* ring, int direction);

// Itérateur
void vertexring_run(vertex_ring* ring, void(*func)(vertex_ring* r, void* args), void* args, int direction);

// I/O
void vertexring_save(vertex_ring* ring, const char* path);

#endif
