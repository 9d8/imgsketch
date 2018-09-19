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
#include <stdlib.h>
#include <time.h>
#include "pngfile.h"
#include "sketcher.h"
#include "presets.h"
#include "bar.h"
#include "arguments.h"

#ifdef JPEG_SUPPORT
#include "jpegfile.h"
#endif

int main(int argc, char** argv) {	
	int (*imagefile_get_data)(FILE* imagefile, struct imagedata* data);
	int (*imagefile_create)(struct imagedata* data, FILE* image);
	char* image_type;

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


	if(pngfile_is_png(image)) {
		imagefile_get_data = &pngfile_get_data;
		imagefile_create = &pngfile_create;
		image_type = "png";
#ifdef JPEG_SUPPORT
	} else if(jpegfile_is_jpeg(image)) {
		imagefile_get_data = &jpegfile_get_data;
		image_type = "jpeg";
	} else {
		printf("%s is not a recognized format.\n", as.infile);
#else
	} else {
		printf("%s is not a png file.\n", as.infile);
#endif
		return 3;
	}

	struct imagedata input_image;
	imagefile_get_data(image, &input_image);

	printf("This is a %s file with dimentions %ix%i.\n", image_type, input_image.width, input_image.height);

	srand(time(NULL));

	struct imagedata canvas;
	imagedata_create_empty(&canvas, input_image.width, input_image.height);
		
	bar_start_stopwatch();
	printf("Creating sketch %s...\n", as.outfile);
	for(int i = 0; i < as.iterations; i++) {
		int color_row_index = rand()%(input_image.height);
		int color_col_index = rand()%(input_image.width);
		struct color source_color = skutil_get_point_color(input_image, color_col_index, color_row_index);
	
		struct point_list* pl = as.preset(as.min_size, as.max_size, input_image.width, input_image.height);

		if(skutil_color_cmp(input_image, source_color, pl) < skutil_cmp(input_image, canvas, pl)) {
			sketcher_draw_point_shape(&canvas, pl, source_color);
		}
		
		sketcher_delete_point_shape(pl);
		
		//thread???
		if(as.sequence_mode && i%1600 == 0) {
			FILE* fp;
			char name[15];
			sprintf(name, "cache/%005i.png", i/1600);

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
