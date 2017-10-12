#include "sketcher.h"
#include <stdio.h>
#include <stdlib.h>

struct point_list* sketch_segment(int x1, int y1, int x2, int y2, int width) {
	struct point_list dummy;
	struct point_list* curr = &dummy;
	dummy.next = NULL;
	
	double m = (y1 - y2)/((double)(x1 - x2));
	
	if(x1 == x2) {
		//a single point will be made at (x2, y2) if x1 == x2
		m = 1;
	}
	
	int xMin = x1 < x2? x1 : x2;
	int xMax = x1 < x2? x2 : x1;

	for(int x = xMin; x <= xMax; x++) {
		struct point_list* node = malloc(sizeof(struct point_list));
	
		double y = m * (x - x2) + y2;
		node->x = x;
		//round or truncate y
		node->y = y + 0.5;
		
		curr->next = node;
		curr = curr->next;
	}	

	int yMin = y1 < y2? y1 : y2;
	int yMax = y1 < y2? y2 : y1;

	m = (x2 - x1)/((double)(y2 - y1));

	for(int y = yMin; y < yMax; y++) {
		struct point_list* node = malloc(sizeof(struct point_list));
		
		double x = m * (y - y2) + x2;
		node->x = x;
		node->y = y;

		curr->next = node;
		curr = curr->next;
	}

	curr->next = NULL;
	return dummy.next;
}

void draw_point_shape(struct png_data* image, struct point_list* shape, struct color color) {
	struct point_list* curr = shape;

	while(curr != NULL) {
		sk_set_point_color(image, curr->x, curr->y, color);
		
		struct color c;
	    c = sk_get_point_color(*image, curr->x, curr->y);
		//printf("At (%i, %i) found %" PRIu8 "\n", curr->x, curr->y, c.red);
		
		curr = curr->next;
	}
}

void delete_point_shape(struct point_list* shape) {
	struct point_list* curr = shape;
	struct point_list* next;

	while(curr != NULL) {
		next = curr->next;
		free(curr);
		curr = next;
	}
}
