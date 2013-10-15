//
//  solve_weight.c
//  Project 3
//

#include <stdio.h>
#include <stdlib.h>

#include "types.h"

// column linked list type
//   I use a linked list since I don't have a maximum Value to go to
typedef struct column_t {
	struct column_t * next; // the next node
	int value; // the column index
	char * using_table; // the jewel usage for this column
	int * weights; // the weights for this column
} column_t;

static char solve_value_sub(jewel_t * jewels, int W, column_t * head, int value_index, int jewel_index) {
	// get the current jewel
	jewel_t * jewel = jewels + jewel_index;
	
	// find all of the relevant columns
	column_t * columns[value_index + 1];
	for (int i = 0; head && i <= value_index; i++, head = head->next)
		columns[i] = head;
	
	// get it's weight
	int weight = jewel->weight;
	
	// assume we're using it
	int using = 1;
	
	// if we need more jewels
	if (value_index > jewel->value) {
		// and there are jewels left
		if (jewel_index > 0) {
			// add the memoized answer for (value_index - jewel->value, jewel_index - 1)
			weight += columns[value_index - jewel->value]->weights[jewel_index - 1];
			
			// if the value is better than above, use it, otherwise not
			using = weight < columns[value_index]->weights[jewel_index - 1];
		} else {
			// can't use this jewel
			using = 0;
		}
	}
	
	// if we're using this one
	if (using)
		// set the cell to the total weight
		columns[value_index]->weights[jewel_index] = weight;
	else {
		// if there's a cell above
		if (jewel_index > 0)
			// use it's value
			columns[value_index]->weights[jewel_index] = columns[value_index]->weights[jewel_index - 1];
		else
			// can't do anything
			columns[value_index]->weights[jewel_index] = 0;
	}
	
	return using;
}

static column_t * alloc_column(int I) {
	column_t * col = malloc(sizeof(column_t));
	
	col->next = NULL;
	col->value = 0;
	col->weights = calloc(I, sizeof(int));
	col->using_table = calloc(I, sizeof(char));
	
	return col;
}

static int column_total(column_t * column, int I) {
	if (!column)
		return -1;
	
	int total = 0;
	for (int i = 0; i < I; i++)
		total += column->weights[i];
	return total;
}

static void free_column(column_t * column) {
	if (column->next)
		free_column(column->next);
	free(column->weights);
	free(column->using_table);
	free(column);
}

void solve_value(jewel_t * jewels, int W, int I) {
	column_t * head;
	
	int V;
	for (column_t * last = NULL, * col; column_total(last, I); last = col) {
		col = alloc_column(I);
		if (last) {
			col->value = last->value + 1;
			last->next = col;
		} else
			head = col;
		
		for (int i = 0; i < I; i++)
			col->using_table[i] = solve_value_sub(jewels, W, head, col->value, i);
		
		V = col->value;
	}
	
	column_t * columns[V], * col = head;
	for (int i = 0; col; i++, col = col->next)
		columns[i] = col;
	
	int imax, vmax;
	for (imax = I - 1; imax >= 0; imax--)
		for (vmax = V - 1; vmax >= 0; vmax--)
			if (columns[vmax]->weights[imax])
				goto stop;
stop:
	
#ifdef DEBUG_OUTPUT
	printf("The min weight is %d using ", columns[vmax]->weights[imax]);
	for (int v = vmax, i = imax; v >= 0 && i >= 0; i--)
		if (columns[v]->using_table[i]) {
			if (v < vmax)
				printf(", ");
			printf("%d", i);
			v -= jewels[i].value;
		}
	printf("\n");
#endif
	
	free_column(head);
}