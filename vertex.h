#ifndef __VERTEX_H__
#define __VERTEX_H__

#include <math.h>
#include <stdlib.h>

/*! Dimensions de l'espace */
#define DIM 2

#define X coords[0]
#define Y coords[1]

/*! Structure pour representer un point. */
typedef struct
{
  double coords[DIM];
} vertex;

vertex* vertex_create(double x, double y);

double vertex_distance(const vertex* v1, const vertex* v2);

#endif
