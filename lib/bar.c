#include "bar.h"
#include <stdio.h>
#include <time.h>

time_t timer;

void start_stopwatch() {
	time(&timer);
}

void print_bar(int width, int progress, int done) {
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
