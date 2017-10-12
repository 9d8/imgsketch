#ifndef COLOR_H_
#define COLOR_H_

#include <stdint.h>

struct color {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
};

int color_distance(struct color c1, struct color c2);

#endif
