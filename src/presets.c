#include "presets.h"
#include <stdlib.h>
#include "sketcher.h"

struct point_list* random_segment(int maxlen, int width, int height) {
	int x1Rand = rand()%(width-1);
	int x2Rand = x1Rand + (rand()%(maxlen*2) - maxlen);
	int y1Rand = rand()%(height-1);
	int y2Rand = y1Rand + (rand()%(maxlen*2) - maxlen);

	if(x2Rand < 0) {
		x2Rand = 0;
	} else if(x2Rand >= width) {
		x2Rand = width - 1;
	}
	
	if(y2Rand < 0) {
		y2Rand = 0;
	} else if(y2Rand >= height) {
		y2Rand = height - 1;
	}
	
	return sketch_segment(x1Rand, y1Rand, x2Rand, y2Rand, 1);
}

struct point_list* random_square(int width, int height) {
	int xRand = rand()%(width-1);
	int yRand = rand()%(height-1);

	return sketch_rectangle(xRand, yRand, 5, 5, width, height);
}
