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

#ifndef COLOR_H_
#define COLOR_H_

#include <stdint.h>

struct color {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
};

int color_get_distance(struct color c1, struct color c2);

#endif
