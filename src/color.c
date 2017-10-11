#include "color.h"
#include <math.h>

int color_distance(struct color c1, struct color c2) {
	//Euclidean distance between two colors
	return sqrt(pow(c1.red - c2.red, 2) + pow(c1.green - c2.green, 2) + pow(c1.blue - c2.blue, 2) + pow(c1.alpha - c2.alpha, 2));		
}
