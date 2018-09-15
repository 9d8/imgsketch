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

#ifndef SKETCHER_H_
#define SKETCHER_H_

#include "imagedata.h"
#include "color.h"
#include "skutil.h"

struct point_list* sketcher_sketch_segment(int x1, int y1, int x2, int y2, int width);
struct point_list* sketcher_sketch_rectangle(int x, int y, int width, int height, int x_bound, int y_bound); 
struct point_list* sketcher_sketch_circle(int x, int y, int radius, int x_bound, int y_bound); 
void sketcher_draw_point_shape(struct imagedata* image, struct point_list* shape, struct color color);
void sketcher_delete_point_shape(struct point_list* shape);

#endif
