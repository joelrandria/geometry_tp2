#ifndef __VERTEX_RING_H__
#define __VERTEX_RING_H__

#include "vertex.h"

// Sens de navigation dans l'anneau
#define VR_BACKWARD 0
#define VR_FORWARD 1
#define BACKWARD siblings[VR_BACKWARD]
#define FORWARD siblings[VR_FORWARD]



typedef struct _vertex_ring
{
  vertex* v;
  struct _vertex_ring* siblings[2];	//0: avant,		1: après
} vertex_ring;

// Création, insertion, ...
vertex_ring* vertexring_create(vertex* v);
vertex_ring* vertexring_add(vertex_ring* ring, vertex* v, const int direction);
vertex_ring* vertexring_enqueue(vertex_ring* ring, vertex* v, const int direction);

// Propriétés basiques
int vertexring_length(vertex_ring* ring);

// Accès aux éléments
vertex_ring* vertexring_last(vertex_ring* ring, const int direction);
vertex* vertexring_findbycoord(vertex_ring* ring, const float x, const float y, const float epsilon);

// Affichage
void vertexring_print(vertex_ring* ring, const int direction);

// Itérateur
void vertexring_run(vertex_ring* ring, void(*func)(vertex_ring* r, void* args), void* args, const int direction);

// I/O
void vertexring_save(vertex_ring* ring, const char* path);
vertex_ring* vertexring_read(const char* path);

#endif
