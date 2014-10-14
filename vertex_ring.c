#include <stdio.h>
#include <stdlib.h>

#include "vertex_ring.h"

vertex_ring* vertexring_create(vertex* v)
{
	vertex_ring* item = malloc(sizeof(vertex_ring));
	item->v = v;
	item->BACKWARD = item;		item->FORWARD = item;

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
vertex_ring* vertexring_last(vertex_ring* ring, const int direction)
{
	vertex_ring* last;

	last = 0;
	vertexring_run(ring, vertexring_last_, &last, VR_FORWARD);

	return last;
}
/*
vertex* vertexring_findbycoord(vertex_ring* ring, const float x, const float y, const float epsilon)
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
}*/

vertex* vertexring_findbycoord(vertex_ring* ring, const float x, const float y, const float epsilon)
{
	if (!ring)
		return NULL;
	const vertex ref = { .X = x, .Y = y };
	//ref.X = x;  ref.Y = y;
	
	const vertex_ring* beginning = ring;
	do
	{
		if (vertex_distance(ring->v, &ref) < epsilon)
			return (ring->v);
		ring = ring->FORWARD;
	}
	while (ring != beginning);

	return NULL;
}

vertex_ring* vertexring_add(vertex_ring* ring, vertex* v, const int direction)
{
	vertex_ring* temp;
	vertex_ring* new_item = vertexring_create(v);

	if (!ring)
		return new_item;

	//on place new_item entre les vertexring temp et ring
	temp = ring->siblings[direction];

	ring->siblings[direction] = new_item;

	new_item->siblings[direction] = temp;
	temp->siblings[!direction] = new_item;

	new_item->siblings[!direction] = ring;

	return new_item;
}
vertex_ring* vertexring_enqueue(vertex_ring* ring, vertex* v, const int direction)
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
	printf("%d %d\r\n", (int)r->v->X, (int)r->v->Y);
}
void vertexring_print(vertex_ring* ring, const int direction)
{
	vertexring_run(ring, vertexring_print_, 0, direction);
}

void vertexring_run(vertex_ring* ring, void(*func)(vertex_ring* r, void* args), void* args, const int direction)
{
	if (!ring)
		return;

	const vertex_ring* beginning = ring;

	func(ring, args);

	while (ring->siblings[direction] != beginning)
	{
		ring = ring->siblings[direction];

		func(ring, args);
	}
}

void vertexring_save_(vertex_ring* r, void* args)
{
	fprintf((FILE*)args, ", %f %f", r->v->X, r->v->Y);
}
void vertexring_save(vertex_ring* ring, const char* path)
{
	FILE* file = NULL; 
	file = fopen(path, "w+");

	if(file == NULL)
	{
		printf("Impossible d'écrire dans le fichier %s\n", path);
		exit(1);
	}

	fprintf(file, "%d", vertexring_length(ring));

	vertexring_run(ring, vertexring_save_, file, VR_FORWARD);

	fprintf(file, "\r\n");

	if(fclose(file) == EOF)
	{
		printf("Problème de fermeture du fichier %s\n", path);
		exit(1);
	}
}


vertex_ring* vertex_ring_read(const char* path)
{
	FILE* file = NULL;
	file = fopen(path, "r");
	if(file == NULL)
	{
		printf("Impossible de lire dans le fichier %s\n", path);
		exit(1);
	}
	
	int count = 0;
	fscanf(file, "%d", &count);
	printf("nombre de points à déclarer : %d\n", count);
	
	vertex_ring* ring = NULL;
	double x = 0, y = 0;
	for(int i = 0;	i < count;	i++)
	{
		//printf("%c\n", fgetc(file));
		fscanf(file, ", %lf %lf", &x, &y);
		//printf("position : %lf %lf\n", x, y);
		ring = vertexring_enqueue(ring, vertex_create(x,y) , VR_FORWARD);
	}
	
	
	if(fclose(file) == EOF)
	{
		printf("Problème de fermeture du fichier %s\n", path);
		exit(1);
	}
	return ring;
}
