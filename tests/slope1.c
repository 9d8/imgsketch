#include <stdio.h>
#include "sketcher.h"

int main() {	
	struct point_list* pl = sketch_segment(0, 0, 10, 10, 1);
	struct point_list* curr = pl;

	while(curr != NULL) {
		printf("(%i, %i) ", curr->x, curr->y);
		curr = curr->next;
	}
	
	printf("\n");
	delete_point_shape(pl);

	return 0;
}
