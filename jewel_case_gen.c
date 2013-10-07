//
//  jewel_case_gen.c
//  Project 3
//

#include <stdio.h>
#include <stdlib.h>

#include "types.h"

static int randint(int n) {
	float r = (float) random();
	r /= RAND_MAX;
	r *= n;
	
	return (int) r;
}

// returns an allocated, randomized list I long with W max weight
jewel_t * generate_jewel_case(int W, int I) {
	// allocate the array
	jewel_t * jewels = calloc(I, sizeof(jewel_t));
	
	printf("Our jewels are (weight, value):\n");
	for (int i = 0; i < I; i++) {
		jewel_t * jewel = jewels + i;
		
		// randomize, a value between 1 and W/2, inclusive
		jewel->weight = randint(W/2 - 1) + 1;
		jewel->value = randint(W/2 - 1) + 1;
		
		printf("%d: %d, %d\n", i + 1, jewel->weight, jewel->value);
	}
	
	return jewels;
}