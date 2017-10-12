#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "pngfile.h"
#include "sketcher.h"
#include "lib/bar.h"

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

	srand(time(NULL));

	struct png_data empty;
	create_empty_png_data(&empty, image_data.width, image_data.height);
		
	struct color* colors = sk_source_colors(image_data);
	
	long int iterations = 500000L;
	start_stopwatch();
	for(int i = 0; i < iterations; i++) {
		int x1Rand = rand()%(image_data.width-1);
		int x2Rand = x1Rand + (rand()%20 - 10);
		int y1Rand = rand()%(image_data.height-1);
		int y2Rand = y1Rand + (rand()%20 - 10);
		int colorIndex = rand()%(image_data.width*image_data.height - 1);
	
		if(x2Rand < 0) {
			x2Rand = 0;
		} else if(x2Rand >= image_data.width) {
			x2Rand = image_data.width - 1;
		}
		
		if(y2Rand < 0) {
			y2Rand = 0;
		} else if(y2Rand >= image_data.height) {
			y2Rand = image_data.height - 1;
		}
		
		struct point_list* pl = sketch_segment(x1Rand, y1Rand, x2Rand, y2Rand, 1);

		if(skclrcmp(image_data, colors[colorIndex], pl) < skcmp(image_data, empty, pl)) {
			draw_point_shape(&empty, pl, colors[colorIndex]);
		}
		
		delete_point_shape(pl);

		printf("Creating sketch... ");
		print_bar(50, i, iterations);
	}

	FILE* fp;
	if((fp = fopen("file.png", "wb")) == NULL) {
		return 1;
	}

	create_png(&empty, fp);
	fclose(fp);

	printf("\n");

	destroy_png_data(&image_data);
	fclose(image);

	return 0;
}
