#include "arguments.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "presets.h"

char* help_string = "Usage: imgsketch [OPTIONS] png\n"
					"\n"
					"Make a unique sketch of a png file.\n"
					"\n"
					"Options:\n"
					" -h\t\tPrint this help.\n"
					" -o PATH\tWrite sketched image to a file. (default: file.png)\n"
					" -l NUM\t\tThe amount of iterations to perform. (default: 1000000)\n"
					" -s\t\tEnable sequencing mode (for creating ffmpeg image sequences).\n" 
					" -m NUM\t\tMinimum shape size. (default: 5)\n"
					" -M NUM\t\tMaximum shape size. (default: 20)\n"
					" -L\t\tUse line segments for sketching. (default)\n"
					" -S\t\tUse squares for sketching.\n"
					" -C\t\tUse circles for sketching.\n";

int arguments_parse(int argc, char** argv, struct arg_settings* as) {
	char* optstring = "o:l:sm:M:LSCh";
	as->iterations = 1000000;
	as->sequence_mode = 0;
	as->min_size = 5;
	as->max_size = 20;
	as->outfile = "file.png";
	as->preset = &presets_random_segment;

	int c;
	while((c = getopt(argc, argv, optstring)) != -1) {
		switch(c) {
			case 'o':
				as->outfile = optarg;
				break;
			case 'l':
				as->iterations = atol(optarg);
				break;
			case 's':
				as->sequence_mode = 1;
				break;
			case 'm':
				as->min_size = atoi(optarg);
				break;
			case 'M':
				as->max_size = atoi(optarg);
				break;
			case 'L':
				as->preset = &presets_random_segment;
				break;
			case 'S':
				as->preset = &presets_random_square;
				break;
			case 'C':
				as->preset = &presets_random_circle;
				break;
			case 'h':
				printf("%s\n", help_string);
				exit(0);
				break;
		}
	}

	if(optind >= argc) {
		return 1;
	}

	as->infile = argv[optind];

	return 0;
}
