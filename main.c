#include "types.h"
#include "functions.h"





int main(int argc, char *argv[]) {
	int W = 200;
	int I = 100;
	
	jewel_t * jewels = generate_jewel_case(W, I);
	
	solve_weight(jewels, W, I);
}