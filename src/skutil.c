#include "skutil.h"
#include <stdio.h>

struct color skutil_get_point_color(struct imagedata d, int x, int y) {
	struct color color; 

	int rowX = x * 4;

	color.red = d.rows[y][rowX];
	color.green = d.rows[y][rowX + 1];
	color.blue = d.rows[y][rowX + 2];
	color.alpha = d.rows[y][rowX + 3];

	return color;
}

void skutil_set_point_color(struct imagedata* d, int x, int y, struct color color) {
	int rowX = x * 4;

	d->rows[y][rowX] = color.red;
	d->rows[y][rowX + 1] = color.green;
	d->rows[y][rowX + 2] = color.blue; 
	d->rows[y][rowX + 3] = color.alpha;
}

int skutil_cmp(struct imagedata source, struct imagedata sketch, struct point_list* cmp_points) {
	int score = 0;
		
	struct point_list* curr = cmp_points;
	
	struct color source_color;
	struct color sketch_color;

	while(curr != NULL) {
		source_color = skutil_get_point_color(source, curr->x, curr->y);
		sketch_color = skutil_get_point_color(sketch, curr->x, curr->y);
		score += color_get_distance(source_color, sketch_color);
		curr = curr->next;
	}

	return score;
}

int skutil_color_cmp(struct imagedata source, struct color sketch_color, struct point_list* cmp_points) {
	int score = 0;
		
	struct point_list* curr = cmp_points;
	
	struct color source_color;

	while(curr != NULL) {
		source_color = skutil_get_point_color(source, curr->x, curr->y);
		score += color_get_distance(source_color, sketch_color);
		curr = curr->next;
	}

	return score;
}
