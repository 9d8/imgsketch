#include "jpegfile.h"
#include <jpeglib.h>
#include <setjmp.h>
#include <stdlib.h>

jmp_buf test;

void libjpeg_error(struct jpeg_common_struct* cinfo) {
	/* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
	struct jpeg_error_mgr* err = (struct jpeg_error_mgr*)cinfo->err;

	/* Always display the message. */
	/* We could postpone this until after returning, if we chose. */
	(*cinfo->err->output_message) (cinfo);
	
	longjmp(test, 1);
}

int jpegfile_is_jpeg(FILE* file) {
	// Rewind in case file has been read from already.
	rewind(file);
	
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	
	jpeg_create_decompress(&cinfo);	

	cinfo.err = jpeg_std_error(&jerr);
	jerr.error_exit = libjpeg_error;

	jpeg_stdio_src(&cinfo, file);

	if(setjmp(test)) {
		jpeg_destroy_decompress(&cinfo);
		return 0;
	}

	jpeg_read_header(&cinfo, 1);
	jpeg_destroy_decompress(&cinfo);
	return 1;
}

int jpegfile_get_data(FILE* jpeg_file, struct imagedata* data) {
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	
	cinfo.err = jpeg_std_error(&jerr);
	jerr.error_exit = libjpeg_error;
	
	if(setjmp(test)) {
		jpeg_destroy_decompress(&cinfo);
		return 0;
	}
	
	jpeg_create_decompress(&cinfo);	
	
	jpeg_stdio_src(&cinfo, jpeg_file);

	// This will store information such as image dimentions in cinfo.
	rewind(jpeg_file);
	jpeg_read_header(&cinfo, TRUE);

	jpeg_start_decompress(&cinfo);

	int row_stride = cinfo.output_width * cinfo.output_components;
	JSAMPARRAY row_pointers = malloc(sizeof(JSAMPROW) * cinfo.output_height);

	while(cinfo.output_scanline < cinfo.output_height) {
		row_pointers[cinfo.output_scanline] = malloc(sizeof(JSAMPLE)*row_stride);
		jpeg_read_scanlines(&cinfo, row_pointers+cinfo.output_scanline, 1);
	}

	data->width = cinfo.output_width;
	data->height = cinfo.output_height;
	data->rows = (uint8_t**) row_pointers;
	data->alpha_channel = 0;
	
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	
	return 1;
}

int jpegfile_create(struct imagedata* data, FILE* image);
