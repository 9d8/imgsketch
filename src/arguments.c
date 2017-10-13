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
					" -s\t\tenable sequencing mode (for creating ffmpeg image sequences)"; 

int parse_args(int argc, char** argv, struct arg_settings* as) {
	char* optstring = "l:sh";
	as->sequence_mode = 0;
	as->iterations = 1000000;
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
