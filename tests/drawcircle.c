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

#include <stdio.h>
#include "sketcher.h"
#include "pngfile.h"

int main() {	
	struct point_list* pl = sketch_circle(50, 50, 30, 100, 100);
	struct point_list* curr = pl;

	while(curr != NULL) {
		printf("(%i, %i) ", curr->x, curr->y);
		curr = curr->next;
	}
	
	struct img_data empty;
	create_empty_img_data(&empty, 100, 100);
			
	struct color red;
	red.red = 255;
	red.green = 0;
	red.blue = 0;
	red.alpha = 255;

	draw_point_shape(&empty, pl, red);
	
	FILE* fp;
	if((fp = fopen("file.png", "wb")) == NULL) {
		return 1;
	}

	create_png(&empty, fp);
	fclose(fp);

	printf("\n");
	delete_point_shape(pl);
	destroy_img_data(&empty);

	return 0;
}
