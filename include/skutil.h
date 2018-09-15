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

#ifndef SKUTIL_H_
#define SKUTIL_H_

#include "imagedata.h"
#include "color.h"

struct point_list {
	int x;
	int y;
	struct point_list* next;
};

struct color skutil_get_point_color(struct imagedata d, int x, int y);
void skutil_set_point_color(struct imagedata* d, int x, int y, struct color color);
int skutil_cmp(struct imagedata source, struct imagedata sketch, struct point_list* cmp_points);
int skutil_color_cmp(struct imagedata source, struct color sketch_color, struct point_list* cmp_points);

#endif
