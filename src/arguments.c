#include "arguments.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char* help_string = "Usage: imgsketch [OPTIONS] png\n"
					"\n"
					"Make a sketch of a png file.\n"
					"\n"
					"Options:\n"
					" -h\t\tprint this help\n"
					" -l\t\tset the amount of iterations to perform (default: 1000000)\n"
					" -s\t\tenable sequencing mode (for creating ffmpeg image sequences)\n" 
					" -m\t\tminimum shape size (default: 5)\n"
					" -M\t\tmaximum shape size (default: 20)\n";

int parse_args(int argc, char** argv, struct arg_settings* as) {
	char* optstring = "l:shm:M:";
	as->iterations = 1000000;
	as->sequence_mode = 0;
	as->min_size = 5;
	as->max_size = 20;
	as->outfile = "file.png";

	int c;
	while((c = getopt(argc, argv, optstring)) != -1) {
		switch(c) {
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
