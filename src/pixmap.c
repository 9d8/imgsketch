#include "pixmap.h"
#include <stdlib.h>


//We may be able to improve upon this once I figure out how to write to a png file
void create_empty_img_data(struct img_data* data, int width, int height) {
	uint8_t** row_pointers = malloc(sizeof(uint8_t*) * height);
	for(int y = 0; y < height; y++) {
		//technically this is hard coding :(
		row_pointers[y] = calloc(width, 4*sizeof(uint8_t));
	}

	data->width = width;
	data->height = height;
	data->rows = row_pointers;
}

void destroy_img_data(struct img_data* data) {	
	for(int y = 0; y < data->height; y++) {
		free(data->rows[y]);
	}
	free(data->rows);
}
