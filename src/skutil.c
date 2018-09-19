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

#include "skutil.h"
#include <stdio.h>

struct color skutil_get_point_color(struct imagedata d, int x, int y) {
	struct color color; 

	/* Subtracting the boolean value for alpha_channel from 4 is a suprisingly
	 * useful hack to obtain the total number of channels */
	int rowX = x * (4 - !d.alpha_channel);

	color.red = d.rows[y][rowX];
	color.green = d.rows[y][rowX + 1];
	color.blue = d.rows[y][rowX + 2];
	color.alpha = d.alpha_channel? d.rows[y][rowX + 3] : 0xFF;

	return color;
}

void skutil_set_point_color(struct imagedata* d, int x, int y, struct color color) {
	int rowX = x * (4 - !d->alpha_channel);

	d->rows[y][rowX] = color.red;
	d->rows[y][rowX + 1] = color.green;
	d->rows[y][rowX + 2] = color.blue; 

	if(d->alpha_channel) {
		d->rows[y][rowX + 3] = color.alpha;
	}
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
