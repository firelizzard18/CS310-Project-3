// 
// solve_density.c
// Project 3
// 
#include "types.h"
#include <stdio.h>
#include <stdlib.h>

int compare_density(const density_t * a, const density_t * b) {
	if (a->density > b->density)
		return -1;
	else if (a->density < b->density)
		return 1;
	else
		return 0;
}

void solve_density(jewel_t * jewels, int W, int I) {

	int total_weight = 0;
	int total_value = 0;

	// Create a density array.
	density_t * densities = malloc(I * sizeof(density_t));

	for (int i = 0; i < I; i++) {
		// Move to the next jewel and store it
		densities[i].jewel = jewels + i;
		// store the density
		densities[i].density = (double)(jewels[i].value) / jewels[i].weight;
	}

	qsort(densities, I, sizeof(density_t), (int (*)(const void *, const void *))&compare_density);

	printf("Items Used: ");

	for (int i = 0; i < I; i++) {

		if (densities[i].jewel->weight <= W - total_weight) {
			printf("%d, ", i+1);
			total_weight += densities[i].jewel->weight;
			total_value += densities[i].jewel->value;
		}

	}
	printf("\x08\x08  \n");
	printf("Total Value: %d\n", total_value);
	printf("Total weight: %d\n", total_weight);


}
