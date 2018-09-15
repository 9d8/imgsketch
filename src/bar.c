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

#include "bar.h"
#include <stdio.h>
#include <time.h>

time_t timer;

void bar_start_stopwatch() {
	time(&timer);
}

void bar_print(int width, int progress, int done) {
	int seconds = difftime(time(NULL), timer);
	int minutes = seconds/60;
	int hours = minutes/60;

	printf("%02i:%02i:%02i", hours, minutes - hours*60, seconds - minutes*60);

	double percent = ((double)progress/1000)/(done/1000);
	printf(" [");
	for(int x = 0; x < width; x++) {
		if(x/((double)width) < percent ) {
			printf("#");
		} else {
			printf("-");
		}
	}

	printf("] %.2f%\r", percent * 100);

	fflush(stdout);

}
