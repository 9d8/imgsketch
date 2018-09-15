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

struct color* skutil_source_colors(struct imagedata source) {
	struct color source_colors[source.height*source.width];
	int i = 0;

	for(int y = 0; y < source.height; y++) {
		for(int x = 0; x < source.width; x++) {
			//could improve results by preventing duplicates (sets)
			source_colors[i++] = skutil_get_point_color(source, x, y);	
		}
	}
	
	struct color* scp = source_colors;
	return scp;
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
