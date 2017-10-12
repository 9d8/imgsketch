#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "pngfile.h"
#include "sketcher.h"

int main(int argc, char** argv) {	
	if(argc <= 1) {
		return 1;
	}
	
	const char* path = *(++argv);
	
	FILE* image = fopen(path, "rb");

	if(image == NULL) {	
		printf("%s does not exist\n", path);
		return 2;
	}

	if(!is_png(image)) {
		printf("Not a png file\n");
		return 3;
	}

	struct png_data image_data;
	get_png_data(image, &image_data);

	printf("This is a png file with dimentions %ix%i\n", image_data.width, image_data.height);
	//printf("%i %i %i %i\n", image_data.rows[182][4], image_data.rows[182][5], image_data.rows[182][6], image_data.rows[182][7]);

	srand(time(NULL));

	struct png_data empty;
	create_empty_png_data(&empty, image_data.width, image_data.height);
	
	for(int i = 0; i < 1000000; i++) {
		int x1Rand = rand()%(image_data.width-1);
		int x2Rand = rand()%(image_data.width-1);
		int y1Rand = rand()%(image_data.height-1);
		int y2Rand = rand()%(image_data.height-1);
		int colorIndex = rand()%(image_data.width*image_data.height - 1);
		
		struct point_list* pl = sketch_segment(x1Rand, y1Rand, x2Rand, y2Rand, 1);
		struct point_list* curr = pl;
		struct color* colors = sk_source_colors(image_data);

		if(skclrcmp(image_data, colors[colorIndex], pl) < skcmp(image_data, empty, pl)) {
			draw_point_shape(&empty, pl, colors[colorIndex]);
		}
		
		delete_point_shape(pl);
	}

	FILE* fp;
	if((fp = fopen("file.png", "wb")) == NULL) {
		return 1;
	}

	create_png(&empty, fp);
	fclose(fp);

//	while(curr != NULL) {
//		printf("(%i, %i) ", curr->x, curr->y);
//		curr = curr->next;
//	}

	printf("\n");

	destroy_png_data(&image_data);
	fclose(image);

	return 0;
}
