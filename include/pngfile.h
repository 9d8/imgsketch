#ifndef PNGFILE_H_
#define PNGFILE_H_

#include <stdio.h>
#include "imagedata.h"

int pngfile_is_png(FILE* file); 
int pngfile_get_data(FILE* png_file, struct imagedata* data);
int pngfile_create(struct imagedata* data, FILE* image);

#endif
