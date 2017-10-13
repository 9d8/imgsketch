#ifndef PNGFILE_H_
#define PNGFILE_H_

#include <stdio.h>
#include "pixmap.h"

int is_png(FILE* file); 
int get_img_data(FILE* png_file, struct img_data* data);
void create_empty_img_data(struct img_data* data, int width, int height);
int create_png(struct img_data* data, FILE* image);
void destroy_img_data(struct img_data* data);

#endif
