#ifndef DARRAY_H
#define DARRAY_H

#include <stdlib.h>
#include <stdio.h>

#include "string.h"

/* Start i32Array declaration */

typedef struct i32Array
{
	int* items;
	unsigned int realSize;
	unsigned int capacity;
} i32Array;

i32Array* initI32Array(unsigned int initCapacity);

void pushI32(i32Array** target, int item);

void printI32Array(i32Array** target);

void freeI32Array(i32Array** target);

/* End i32Array declaration */

/* Start f32Array declaration */

typedef struct f32Array
{
	float* items;
	unsigned int realSize;
	unsigned int capacity;
} f32Array;

f32Array* initF32Array(unsigned int initCapacity);

void pushF32(f32Array** target, float item);

void printF32Array(f32Array** target);

void freeF32Array(f32Array** target);

/* End f32Array declaration */

/* Start f64Array declaration */

typedef struct f64Array
{
	double* items;
	unsigned int realSize;
	unsigned int capacity;
} f64Array;

f64Array* initF64Array(unsigned int initCapacity);

void pushF64(f64Array** target, double item);

void printF64Array(f64Array** target);

void freeF64Array(f64Array** target);

/* End f64Array declaration */

#endif // DARRAY_H