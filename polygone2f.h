#ifndef __POLYGONE2F_H__
#define __POLYGONE2F_H__

#include "vertex2f.h"
#include "rect2f.h"

vertex2f* get_polygone2f_min_lex(vertex2f* polygone);
int get_polygone2f_rotation_direction(vertex2f* polygone);
rect2f* get_polygone2f_bounding_rect(vertex2f* polygone);
int locate_vertex_polygone2f(vertex2f* polygone, vertex2f* p);

#endif
