#include <stdio.h>
#include <stdlib.h>
#include "time.h"

int main() {	
	srand(time(NULL));
	
	int maxlen = 9;
	int minlen = 0;

	for(int i = 0; i < 100; i++) {
		int r = rand()%(2*(maxlen - minlen + 1)) + minlen;
		r -= r < maxlen + 1? maxlen + minlen : maxlen - minlen + 1;

		printf("%i ", r);
	}

	return 0;
}
