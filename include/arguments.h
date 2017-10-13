#ifndef ARGUMENTS_H_
#define ARGUMENTS_H_

struct arg_settings {
	char* infile;
	char* outfile;
	long int iterations;
	int sequence_mode;
};

int parse_args(int argc, char** argv, struct arg_settings* as);

#endif
