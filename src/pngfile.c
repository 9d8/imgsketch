/*
	This file belongs to imgsketch, a tool for creating a unique sketch of a 
	png.
	Copyright (C) 2018 9d8

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

	https://github.com/9d8/tmm/
*/

#include "pngfile.h"
#include <png.h>
#include <stdlib.h>

int pngfile_is_png(FILE* file) {
	// Rewind in case file has been read from already.
	rewind(file);	
	
	char header[8];
	fread(header, 1, 8, file);

	return !png_sig_cmp(header, 0, 8);
}

int pngfile_get_data(FILE* png_file, struct imagedata* data) {
	png_uint_32 width;
	png_uint_32 height;
	png_byte color_type;
	png_byte bit_depth;

	//initialize png file for reading
	png_structp png;
	if(!(png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL))) {
		return 1;
	}

    png_infop info;
	if(!(info = png_create_info_struct(png))) {
		png_destroy_read_struct(&png, NULL, NULL);
		return 1;
	}
	
	//catch any linpng exceptions
	if(setjmp(png_jmpbuf(png))) {
       png_destroy_read_struct(&png, &info, NULL);
       return 1;
    }

	//read header data
	rewind(png_file);
	png_init_io(png, png_file);
	png_read_info(png, info);

	width = png_get_image_width(png, info);
	height = png_get_image_height(png, info); 
	color_type = png_get_color_type(png, info);
	bit_depth = png_get_bit_depth(png, info);

	//convert image color_types to 8 bit depth RGBA
	if (color_type == PNG_COLOR_TYPE_PALETTE) {
        png_set_palette_to_rgb(png);
	}

    if (png_get_valid(png, info, PNG_INFO_tRNS)) {
		png_set_tRNS_to_alpha(png);
	}

    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) {
		png_set_expand_gray_1_2_4_to_8(png);
	}
	 
	if (bit_depth == 16) {
       png_set_scale_16(png);
	}
	
	if(color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_PALETTE) {
		png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
	}

	if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
		png_set_gray_to_rgb(png);
	}
	
	png_read_update_info(png, info);

	//read image
	png_bytepp row_pointers = malloc(sizeof(png_bytep) * height);
	for(int y = 0; y < height; y++) {
		row_pointers[y] = malloc(png_get_rowbytes(png,info));
	}

	png_read_image(png, row_pointers);
	
	data->width = width;
	data->height = height;
	data->rows = (uint8_t**) row_pointers;
	data->alpha_channel = 1;

	png_destroy_read_struct(&png, &info, NULL);
	return 0;
}

int pngfile_create(struct imagedata* data, FILE* image) {
	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!png_ptr) {
		fclose(image);
		return 1;
	}

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if(!info_ptr) {
		png_destroy_write_struct(&png_ptr, NULL);
		fclose(image);
		return 1;
    }

	if(setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(image);
		return 1;
    }

	png_init_io(png_ptr, image);

	png_set_IHDR(png_ptr, info_ptr, data->width, data->height, 8, 
		PNG_COLOR_TYPE_RGB_ALPHA,
		PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_DEFAULT);
	
	png_bytepp row_pointers = data->rows;

 	png_set_rows(png_ptr, info_ptr, row_pointers);
	png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
}
