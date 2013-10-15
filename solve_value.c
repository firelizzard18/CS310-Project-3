//
//  solve_weight.c
//  Project 3
//

#include <stdio.h>
#include <stdlib.h>

#include "types.h"

typedef struct column_t {
	struct column_t * next;
	int value;
	int * values;
	char * using;
} column_t;

static char solve_value_sub(jewel_t * jewels, int W, column_t * head, int value_index, int jewel_index) {
	jewel_t * jewel = jewels + jewel_index;
	
	column_t * columns[value_index + 1];
	for (int i = 0; head; i++, head = head->next)
		columns[i] = head;
	
	if (value_index > jewel->value) {
		if (jewel_index > 0)
			columns[value_index]->values[jewel_index] = columns[value_index]->values[jewel_index - 1];
		else
			columns[value_index]->values[jewel_index] = 0;
		return 0;
		
	}
	
	int weight = jewel->weight;
	
	int using = 1;
	
	if (value_index > jewel->value && jewel_index > 0) {
		weight += columns[value_index - jewel->value]->values[jewel_index - 1];
		using = weight < columns[value_index]->values[jewel_index - 1];
	}
	
	if (using)
		columns[value_index]->values[jewel_index] = weight;
	else
		columns[value_index]->values[jewel_index] = columns[value_index]->values[jewel_index - 1];
	
	return using;
}

static column_t * alloc_column(int I) {
	column_t * col = malloc(sizeof(column_t));
	
	col->next = NULL;
	col->value = 0;
	col->values = calloc(I, sizeof(int));
	col->using = calloc(I, sizeof(char));
	
	return col;
}

static int column_total(column_t * column, int I) {
	if (!column)
		return -1;
	
	int total = 0;
	for (int i = 0; i < I; i++)
		total += column->values[i];
	return total;
}

static void free_column(column_t * column) {
	if (column->next)
		free_column(column->next);
	free(column->values);
	free(column->using);
	free(column);
}

void solve_value(jewel_t * jewels, int W, int I) {
	column_t * head;
	
	int V;
	for (column_t * last = NULL, * col; column_total(col, I); last = col) {
		col = alloc_column(I);
		if (last) {
			col->value = last->value + 1;
			last->next = col;
		} else
			head = col;
		
		for (int i = 0; i < I; i++)
			col->using[i] = solve_value_sub(jewels, W, head, col->value, i);
		
		V = col->value;
	}
	
	column_t * columns[V], * col = head;
	for (int i = 0; col; i++, col = col->next)
		columns[i] = col;
	
	int imax, vmax;
	for (imax = I - 1; imax >= 0; imax--)
		for (vmax = V - 1; vmax >= 0; vmax--)
			if (columns[vmax]->values[imax])
				goto stop;
stop:
	
	printf("The max value is %d using ", columns[vmax]->values[imax]);
	for (int v = vmax, i = imax; v >= 0 && i >= 0; i--)
		if (columns[v]->using[i]) {
			if (v < vmax)
				printf(", ");
			printf("%d", i);
			v -= jewels[i].value;
		}
	printf("\n");
	
	free_column(head);
}