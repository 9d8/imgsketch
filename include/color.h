#ifndef COLOR_H_
#define COLOR_H_

struct color {
	char red;
	char green;
	char blue;
	char alpha;
};

int color_distance(struct color c1, struct color c2);

#endif
