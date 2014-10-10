#include "vertex.h"


vertex* vertex_create(const double x, const double y)
{
  vertex* v = malloc(sizeof(*v));
  v->X = x;
  v->Y = y;

  return v;
}

//float vertex_distance(vertex* v1, vertex* v2)
//conversion double vers float alors que tout est en double.
double vertex_distance(const vertex* v1, const vertex* v2)
{
	return hypot(v2->Y - v1->Y, v2->X - v1->X);
	//return sqrt(pow((v2->Y - v1->Y), 2) + pow((v2->X - v1->X), 2));
}
