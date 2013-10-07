//
//  solve_weight.c
//  Project 3
//
//  Created by Ethan Reesor on 10/7/13.
//  Copyright (c) 2013 Ethan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "types.h"

// solve the subproblem for the specified indicies
static char solve_weight_sub(jewel_t * jewels, int ** table_weight, int weight_index, int jewel_index) {
	// get the current jewel
	jewel_t * jewel = jewels + jewel_index;
	
	
	// if the current jewel is too big
	if (weight_index < jewel->weight) {
		// if there's a row above this
		if (jewel_index > 0)
			// use that value
			table_weight[weight_index][jewel_index] = table_weight[weight_index][jewel_index - 1];
		else
			// nothing to do
			table_weight[weight_index][jewel_index] = 0;
		// we can't add this jewel
		return 0;
	}
	
	// get it's value
	int value = jewel->value;
	
	// assume we're using it
	int using = 1;
	
	// if we can fit more jewels and there are jewels left
	if (weight_index > jewel->weight && jewel_index > 0) {
		// add the memoized answer for (weight_index - jewel->weight, jewel_index - 1)
		value += table_weight[weight_index - jewel->weight][jewel_index - 1];
		
		// if the value is better than above, use it, otherwise not
		using = value > table_weight[weight_index][jewel_index - 1];
	}
	
	// if we're using this jewel
	if (using)
		// set the cell to the total value
		table_weight[weight_index][jewel_index] = value;
	else
		// set the cell to the cell above
		table_weight[weight_index][jewel_index] = table_weight[weight_index][jewel_index - 1];
	
	return using;
}

// solve the problem using I items with max weight W
void solve_weight(jewel_t * jewels, int W, int I) {
	// jewels is indexed from 0, but we want to index it from 1, so:
	jewels--;
	
	// allocate
	int ** weights = calloc(W + 1, sizeof(int *));
	char ** using = calloc(W + 1, sizeof(char *));
	for (int w = 0; w <= W; w++) {
		weights[w] = calloc(I + 1, sizeof(int));
		using[w] = calloc(I + 1, sizeof(char));
	}
	
	// solve each subproblem
	for (int i = 1; i <= I; i++)
		for (int w = 1; w <= W; w++)
			using[w][i] = solve_weight_sub(jewels, weights, w, i);
	
	// print out the result
	printf("The max value is %d using ", weights[W][I]);
	for (int w = W, i = I; w > 0 && i > 0; i--)
		if (using[w][i]) {
			printf("%d", i);
			w -= jewels[i].weight;
			if (w >= 0)
				printf(", ");
		}
	printf("\n");
	
	// deallocate
	for (int w = 0; w <= W; w++) {
		free(weights[w]);
		free(using[w]);
	}
	free(weights);
	free(using);
}