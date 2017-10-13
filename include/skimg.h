#ifndef SKIMG_H_
#define SKIMG_H_

#include "pixmap.h"
#include "color.h"

struct color sk_get_point_color(struct img_data d, int x, int y);
void sk_set_point_color(struct img_data* d, int x, int y, struct color color);
struct color* sk_source_colors(struct img_data source);
int skcmp(struct img_data source, struct img_data sketch, struct point_list* cmp_points);
int skclrcmp(struct img_data source, struct color sketch_color, struct point_list* cmp_points);

#endif
