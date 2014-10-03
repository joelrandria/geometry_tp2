#ifndef __RECT2F_H__
#define __RECT2F_H__

#include "vertex2f.h"

typedef struct rect2f
{
  vertex2f* down_left;
  vertex2f* down_right;
  vertex2f* up_right;
  vertex2f* up_left;
} rect2f;

rect2f* new_rect2f();
float get_rect2f_width(rect2f* rect);
float get_rect2f_height(rect2f* rect);

#endif
