#ifndef PRESETS_H_
#define PRESETS_H_

#include "skutil.h"

struct point_list* presets_random_segment(int minlen, int maxlen, int width, int height);
struct point_list* presets_random_square(int minlen, int maxlen, int width, int height);
struct point_list* presets_random_circle(int minrad, int maxrad, int width, int height);

#endif
