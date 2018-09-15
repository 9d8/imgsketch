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
		
	bar_start_stopwatch();
	printf("Creating sketch %s...\n", as.outfile);
	for(int i = 0; i < as.iterations; i++) {
		int color_row_index = rand()%(input_image.height);
		int color_col_index = rand()%(input_image.width);
		struct color source_color = skutil_get_point_color(input_image, color_col_index, color_row_index);
	
		struct point_list* pl = as.preset(5, 20, input_image.width, input_image.height);

		if(skutil_color_cmp(input_image, source_color, pl) < skutil_cmp(input_image, canvas, pl)) {
			sketcher_draw_point_shape(&canvas, pl, source_color);
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
