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

#ifndef PRESETS_H_
#define PRESETS_H_

#include "skutil.h"

struct point_list* presets_random_segment(int minlen, int maxlen, int width, int height);
struct point_list* presets_random_square(int minlen, int maxlen, int width, int height);
struct point_list* presets_random_circle(int minrad, int maxrad, int width, int height);

#endif
