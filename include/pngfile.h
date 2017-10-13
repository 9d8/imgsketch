#ifndef PNGFILE_H_
#define PNGFILE_H_

#include <stdio.h>
#include "pixmap.h"

int is_png(FILE* file); 
int get_png_data(FILE* png_file, struct img_data* data);
int create_png(struct img_data* data, FILE* image);

#endif
