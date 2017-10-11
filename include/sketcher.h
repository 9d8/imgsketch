#ifndef SKETCHER_H_
#define SKETCHER_H_

#include "pnggrid.h"
#include "color.h"
#include "skimg.h"

struct point_list* sketch_segment(int x1, int y1, int x2, int y2, int width);
void draw_point_shape(struct png_data* image, struct point_list* shape, struct color color);
void delete_point_shape(struct point_list* shape);

#endif
