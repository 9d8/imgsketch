#ifndef PNGGRID_H_
#define PNGGRID_H_

#include <stdint.h>

struct img_data {
	int width;
	int height;
	uint8_t** rows;
};

struct point_list {
	int x;
	int y;
	struct point_list* next;
};

#endif
