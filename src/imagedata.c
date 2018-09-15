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
