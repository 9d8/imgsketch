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

#include "sketcher.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct point_list* sketcher_sketch_segment(int x1, int y1, int x2, int y2, int width) {
	struct point_list dummy;
	struct point_list* curr = &dummy;
	dummy.next = NULL;
	
	double mx = (y1 - y2)/((double)(x1 - x2));
	double my = (x2 - x1)/((double)y2 - y1);
	
	int xMin = x1 < x2? x1 : x2;
	int xMax = x1 < x2? x2 : x1;
	int yMin = y1 < y2? y1 : y2;
	int yMax = y1 < y2? y2 : y1;

	if(x1 == x2) {
		mx = 0;
		yMin++;
	}

	if(y1 == y2) {
		my = 0;
		xMin++;
	}

	if(mx == 0 && my == 0) {
			struct point_list* node = malloc(sizeof(struct point_list));
		
			node->x = x1;
			node->y = y1;
			
			curr->next = node;
			curr = curr->next;
	} else {
		for(int x = xMin; x <= xMax; x++) {
			struct point_list* node = malloc(sizeof(struct point_list));
		
			double y = mx * (x - x2) + y2;
			node->x = x;
			//round or truncate y
			node->y = y + 0.5;
			
			curr->next = node;
			curr = curr->next;
		}	

		for(int y = yMin; y <= yMax; y++) {
			if(fmod(y, mx) == 0) {
				continue;
			}
			//printf("%i - %f\n", y, fmod(y,mx));

			struct point_list* node = malloc(sizeof(struct point_list));
			
			double x = my * (y - y2) + x2;
			node->x = x;
			node->y = y;

			curr->next = node;
			curr = curr->next;
		}
	}

	curr->next = NULL;
	return dummy.next;
}

struct point_list* sketcher_sketch_rectangle(int x, int y, int width, int height, int x_bound, int y_bound) {
	struct point_list dummy;
	struct point_list* curr = &dummy;
	dummy.next = NULL;

	for(int w = -width/2; w < width - width/2; w++) {
		for(int h = -height/2; h < height - height/2; h++) {
			int draw_x = x + w;
			int draw_y = y + h;

			if(draw_x >= 0 && draw_x < x_bound 
					&& draw_y >= 0 && draw_y < y_bound) {
				struct point_list* node = malloc(sizeof(struct point_list));
				
				node->x = draw_x;
				node->y = draw_y;

				curr->next = node;
				curr = curr->next;
			}
		}
	}
	
	curr->next = NULL;
	return dummy.next;
}

struct point_list* sketcher_sketch_circle(int x, int y, int radius, int x_bound, int y_bound) {
	struct point_list dummy;
	struct point_list* curr = &dummy;
	dummy.next = NULL;
	
	for(int h=-radius; h<=radius; h++) {
		for(int w=-radius; w<=radius; w++) {
			if(w*w+h*h <= radius*radius + radius 
					&& x + w >= 0 && x + w < x_bound
					&& y + h >= 0 && y + h < y_bound) {
				struct point_list* node = malloc(sizeof(struct point_list));
				
				node->x = x + w;
				node->y = y + h;

				curr->next = node;
				curr = curr->next;
			}
		}
	}

	curr->next = NULL;
	return dummy.next;
}	

void sketcher_draw_point_shape(struct imagedata* image, struct point_list* shape, struct color color) {
	struct point_list* curr = shape;

	while(curr != NULL) {
		skutil_set_point_color(image, curr->x, curr->y, color);
		
		//struct color c;
	    //c = sk_get_point_color(*image, curr->x, curr->y);
		//printf("At (%i, %i) found %" PRIu8 "\n", curr->x, curr->y, c.red);
		
		curr = curr->next;
	}
}

void sketcher_delete_point_shape(struct point_list* shape) {
	struct point_list* curr = shape;
	struct point_list* next;

	while(curr != NULL) {
		next = curr->next;
		free(curr);
		curr = next;
	}
}
