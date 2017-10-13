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
	
	struct png_data empty;
	create_empty_png_data(&empty, 100, 100);
			
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
	destroy_png_data(&empty);

	return 0;
}