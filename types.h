//
//  types.h
//  Project 3
//

#ifndef Project_3_types_h
#define Project_3_types_h

typedef struct jewel_t {
	unsigned int weight, value;
} jewel_t;

typedef struct density_t {
	jewel_t * jewel;
	double density;
} density_t;

#endif
