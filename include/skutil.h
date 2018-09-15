#ifndef SKUTIL_H_
#define SKUTIL_H_

#include "imagedata.h"
#include "color.h"

struct point_list {
	int x;
	int y;
	struct point_list* next;
};

struct color skutil_get_point_color(struct imagedata d, int x, int y);
void skutil_set_point_color(struct imagedata* d, int x, int y, struct color color);
int skutil_cmp(struct imagedata source, struct imagedata sketch, struct point_list* cmp_points);
int skutil_color_cmp(struct imagedata source, struct color sketch_color, struct point_list* cmp_points);

#endif
