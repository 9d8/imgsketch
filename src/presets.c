/*
	This file belongs to imgsketch, a tool for creating a unique sketch of a 
	png.
	Copyright (C) 2018 9d8

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

	https://github.com/9d8/tmm/
*/

#include "presets.h"
#include <stdlib.h>
#include "sketcher.h"

static int plus_minus_rand_range(int min, int max);

struct point_list* presets_random_segment(int minlen, int maxlen, int width, int height) {
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
	
	return sketcher_sketch_segment(x1Rand, y1Rand, x2Rand, y2Rand, 1);
}

struct point_list* presets_random_square(int minlen, int maxlen, int width, int height) {
	int xRand = rand()%(width-1);
	int yRand = rand()%(height-1);
	int sRand = rand()%(maxlen - minlen + 1) + minlen;

	return sketcher_sketch_rectangle(xRand, yRand, sRand, sRand, width, height);
}

struct point_list* presets_random_circle(int minrad, int maxrad, int width, int height) {
	int xRand = rand()%(width-1);
	int yRand = rand()%(height-1);
	int rRand = rand()%maxrad;

	return sketcher_sketch_circle(xRand, yRand, rRand, width, height);
}

int plus_minus_rand_range(int min, int max) {
	int r = rand()%(2*(max - min + 1)) + min;
	r -= r < max + 1? max + min : max - min + 1;
	return r;
}
