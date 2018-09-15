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

#include "color.h"
#include <math.h>

int color_get_distance(struct color c1, struct color c2) {
	//Euclidean distance between two colors
	return sqrt(pow(c1.red - c2.red, 2) + pow(c1.green - c2.green, 2) + pow(c1.blue - c2.blue, 2) + pow(c1.alpha - c2.alpha, 2));		
}
