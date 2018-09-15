#ifndef ARGUMENTS_H_
#define ARGUMENTS_H_

#include "skutil.h"

struct arg_settings {
	char* infile;
	char* outfile;
	long int iterations;
	int sequence_mode;
	unsigned int min_size;
	unsigned int max_size;
	struct point_list* (*preset)(int min, int max, int width, int height);
};

int arguments_parse(int argc, char** argv, struct arg_settings* as);

#endif
