//
//  main.c
//  Project 3
//

#include "types.h"
#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef void (*solve_func)(jewel_t *, int, int);

double time_solve(jewel_t ** cases, int iter, int W, int I, solve_func func) {
	struct timeval tv1, tv2;
	
	gettimeofday(&tv1, NULL);
	for (int i = 0; i < iter; i++)
		func(cases[i], W, I);
	gettimeofday(&tv2, NULL);
	
	return (double) (tv2.tv_sec - tv1.tv_sec) * 1000 + (double) (tv2.tv_usec - tv1.tv_usec) / 1000;
}

int main(int argc, char *argv[]) {
	int iter = 1000;
	int W = 200;
	int I = 500;
	
	jewel_t ** cases = malloc(iter * sizeof(jewel_t *));
	for (int i = 0; i < iter; i++)
		cases[i] = generate_jewel_case(W, I);
	
	printf("Time for density: %fms\n", time_solve(cases, iter, W, I, &solve_density));
	printf("Time for value: %fms\n", time_solve(cases, iter, W, I, &solve_value));
	printf("Time for weight: %fms\n", time_solve(cases, iter, W, I, &solve_weight));
	
	for (int i = 0; i < iter; i++)
		free(cases[i]);
	free(cases);
}