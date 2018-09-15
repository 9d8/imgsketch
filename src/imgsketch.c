#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pngfile.h"
#include "sketcher.h"
#include "presets.h"
#include "bar.h"
#include "arguments.h"

int main(int argc, char** argv) {	
	
	struct arg_settings as;
	if(arguments_parse(argc, argv, &as)) {
		printf("Need path argument.\n");
		return 1;	
	}
	
	FILE* image = fopen(as.infile, "rb");

	if(image == NULL) {	
		printf("%s does not exist.\n", as.infile);
		return 2;
	}

	if(!pngfile_is_png(image)) {
		printf("%s is not a png file.\n", as.infile);
		return 3;
	}

	struct imagedata input_image;
	pngfile_get_data(image, &input_image);

	printf("This is a png file with dimentions %ix%i.\n", input_image.width, input_image.height);

	srand(time(NULL));

	struct imagedata canvas;
	imagedata_create_empty(&canvas, input_image.width, input_image.height);
		
	struct color* source_colors = skutil_source_colors(input_image);
	
	bar_start_stopwatch();
	for(int i = 0; i < as.iterations; i++) {
		int colorIndex = rand()%(input_image.width*input_image.height - 1);
	
		//struct point_list* pl = random_square(as.min_size, as.max_size, input_image.width, input_image.height);
		//struct point_list* pl = random_circle(5, 20, input_image.width, input_image.height);
		struct point_list* pl = presets_random_segment(5, 20, input_image.width, input_image.height);

		if(skutil_color_cmp(input_image, source_colors[colorIndex], pl) < skutil_cmp(input_image, canvas, pl)) {
			sketcher_draw_point_shape(&canvas, pl, source_colors[colorIndex]);
		}
		
		sketcher_delete_point_shape(pl);
		
		//thread???
		if(as.sequence_mode && i%1600 == 0) {
			FILE* fp;
			char name[15];
			sprintf(name, "cache/%003i.png", i/1600);

			if((fp = fopen(name, "wb")) == NULL) {
				return 1;
			}

			pngfile_create(&canvas, fp);
			fclose(fp);
		}

		printf("Creating sketch... ");
		bar_print(50, i, as.iterations);
	}

	FILE* fp;
	if((fp = fopen(as.outfile, "wb")) == NULL) {
		return 1;
	}

	pngfile_create(&canvas, fp);
	fclose(fp);

	printf("\n");

	imagedata_destroy(&input_image);
	imagedata_destroy(&canvas);
	fclose(image);

	return 0;
}
