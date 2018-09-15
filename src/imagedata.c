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

#include "imagedata.h"
#include <stdlib.h>

void imagedata_create_empty(struct imagedata* data, int width, int height) {
	uint8_t** row_pointers = malloc(sizeof(uint8_t*) * height);
	for(int y = 0; y < height; y++) {
		row_pointers[y] = calloc(width, 4*sizeof(uint8_t));
	}

	data->width = width;
	data->height = height;
	data->rows = row_pointers;
}

void imagedata_destroy(struct imagedata* data) {	
	for(int y = 0; y < data->height; y++) {
		free(data->rows[y]);
	}
	free(data->rows);
}
