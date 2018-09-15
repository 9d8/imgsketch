#ifndef IMAGEDATA_H_
#define IMAGEDATA_H_

#include <stdint.h>

struct imagedata {
	int width;
	int height;
	uint8_t** rows;
};

void imagedata_create_empty(struct imagedata* data, int width, int height);
void imagedata_destroy(struct imagedata* data);

#endif
