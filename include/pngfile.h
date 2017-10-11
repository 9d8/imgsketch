#ifndef PNGFILE_H_
#define PNGFILE_H_

#include <stdio.h>
#include "pnggrid.h"

int is_png(FILE* file); 
int get_png_data(FILE* png_file, struct png_data* data);
void create_empty_png_data(struct png_data* data, int width, int height);
void destroy_png_data(struct png_data* data);

#endif
