#ifndef SKIMG_H_
#define SKIMG_H_

#include "pixmap.h"
#include "color.h"

struct color sk_get_point_color(struct png_data d, int x, int y);
void sk_set_point_color(struct png_data* d, int x, int y, struct color color);
struct color* sk_source_colors(struct png_data source);
int skcmp(struct png_data source, struct png_data sketch, struct point_list* cmp_points);
int skclrcmp(struct png_data source, struct color sketch_color, struct point_list* cmp_points);

#endif
