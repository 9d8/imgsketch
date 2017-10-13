#include "skimg.h"
#include <stdio.h>

struct color sk_get_point_color(struct img_data d, int x, int y) {
	struct color color; 

	int rowX = x * 4;

	color.red = d.rows[y][rowX];
	color.green = d.rows[y][rowX + 1];
	color.blue = d.rows[y][rowX + 2];
	color.alpha = d.rows[y][rowX + 3];

	return color;
}

void sk_set_point_color(struct img_data* d, int x, int y, struct color color) {
	int rowX = x * 4;

	d->rows[y][rowX] = color.red;
	d->rows[y][rowX + 1] = color.green;
	d->rows[y][rowX + 2] = color.blue; 
	d->rows[y][rowX + 3] = color.alpha;
}

struct color* sk_source_colors(struct img_data source) {
	struct color source_colors[source.height*source.width];
	int i = 0;

	for(int y = 0; y < source.height; y++) {
		for(int x = 0; x < source.width; x++) {
			//could improve results by preventing duplicates (sets)
			source_colors[i++] = sk_get_point_color(source, x, y);	
		}
	}
	
	struct color* scp = source_colors;
	return scp;
}


int skcmp(struct img_data source, struct img_data sketch, struct point_list* cmp_points) {
	int score = 0;
		
	struct point_list* curr = cmp_points;
	
	struct color source_color;
	struct color sketch_color;

	while(curr != NULL) {
		source_color = sk_get_point_color(source, curr->x, curr->y);
		sketch_color = sk_get_point_color(sketch, curr->x, curr->y);
		score += color_distance(source_color, sketch_color);
		curr = curr->next;
	}

	return score;
}

int skclrcmp(struct img_data source, struct color sketch_color, struct point_list* cmp_points) {
	int score = 0;
		
	struct point_list* curr = cmp_points;
	
	struct color source_color;

	while(curr != NULL) {
		source_color = sk_get_point_color(source, curr->x, curr->y);
		score += color_distance(source_color, sketch_color);
		curr = curr->next;
	}

	return score;
}
