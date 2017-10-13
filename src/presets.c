#include "presets.h"
#include <stdlib.h>
#include "sketcher.h"

int plus_minus_rand_range(int min, int max);

struct point_list* random_segment(int minlen, int maxlen, int width, int height) {
	int x1Rand = rand()%(width-1);
	int x2Rand = x1Rand + plus_minus_rand_range(minlen, maxlen);
	int y1Rand = rand()%(height-1);
	int y2Rand = y1Rand + plus_minus_rand_range(minlen, maxlen);

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

struct point_list* random_square(int maxlen, int width, int height) {
	int xRand = rand()%(width-1);
	int yRand = rand()%(height-1);
	int sRand = rand()%maxlen;

	return sketch_rectangle(xRand, yRand, sRand, sRand, width, height);
}

struct point_list* random_circle(int minrad, int maxrad, int width, int height) {
	int xRand = rand()%(width-1);
	int yRand = rand()%(height-1);
	int rRand = rand()%maxrad;

	return sketch_circle(xRand, yRand, rRand, width, height);
}

int plus_minus_rand_range(int min, int max) {
	int r = rand()%(2*(max - min + 1)) + min;
	r -= r < max + 1? max + min : max - min + 1;
	return r;
}
