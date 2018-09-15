#ifndef SKETCHER_H_
#define SKETCHER_H_

#include "imagedata.h"
#include "color.h"
#include "skutil.h"

struct point_list* sketcher_sketch_segment(int x1, int y1, int x2, int y2, int width);
struct point_list* sketcher_sketch_rectangle(int x, int y, int width, int height, int x_bound, int y_bound); 
struct point_list* sketcher_sketch_circle(int x, int y, int radius, int x_bound, int y_bound); 
void sketcher_draw_point_shape(struct imagedata* image, struct point_list* shape, struct color color);
void sketcher_delete_point_shape(struct point_list* shape);

#endif
