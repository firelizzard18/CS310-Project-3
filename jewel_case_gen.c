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
		jewels[i].weight = randint(W/2);
		jewels[i].value = randint(W/2);
		
		printf("%d: %d, %d\n", i + 1, jewels[i].weight, jewels[i].value);
	}
	
	return jewels;
}