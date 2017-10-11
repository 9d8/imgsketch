#ifndef PNGGRID_H_
#define PNGGRID_H_

struct png_data {
	int width;
	int height;
	unsigned char** rows;
};

struct point_list {
	int x;
	int y;
	struct point_list* next;
};

#endif
