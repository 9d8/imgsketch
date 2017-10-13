#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pngfile.h"
#include "sketcher.h"
#include "presets.h"
#include "lib/bar.h"
#include "arguments.h"

int main(int argc, char** argv) {	
	
	struct arg_settings as;
	if(parse_args(argc, argv, &as)) {
		printf("Need path argument");
		return 1;	
	}

	
	FILE* image = fopen(as.infile, "rb");

	if(image == NULL) {	
		printf("%s does not exist\n", as.infile);
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
	
	start_stopwatch();
	for(int i = 0; i < as.iterations; i++) {
		int colorIndex = rand()%(image_data.width*image_data.height - 1);
	
		struct point_list* pl = random_square(as.min_size, as.max_size, image_data.width, image_data.height);
		//struct point_list* pl = random_circle(5, 20, image_data.width, image_data.height);
		//struct point_list* pl = random_segment(5, 20, image_data.width, image_data.height);

		if(skclrcmp(image_data, colors[colorIndex], pl) < skcmp(image_data, empty, pl)) {
			draw_point_shape(&empty, pl, colors[colorIndex]);
		}
		
		delete_point_shape(pl);
		
		if(as.sequence_mode && i%10000 == 0) {
			FILE* fp;
			char name[15];
			sprintf(name, "cache/%003i.png", i/10000);

			if((fp = fopen(name, "wb")) == NULL) {
				return 1;
			}

			create_png(&empty, fp);
			fclose(fp);
		}

		printf("Creating sketch... ");
		print_bar(50, i, as.iterations);
	}

	FILE* fp;
	if((fp = fopen(as.outfile, "wb")) == NULL) {
		return 1;
	}

	create_png(&empty, fp);
	fclose(fp);

	printf("\n");

	destroy_png_data(&image_data);
	destroy_png_data(&empty);
	fclose(image);

	return 0;
}
