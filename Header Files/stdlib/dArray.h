#ifndef DARRAY_H
#define DARRAY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "string.h"

/* Start i32Array declaration */
typedef struct i32Array
{
	int* items;
	unsigned int realSize;
	unsigned int capacity;
} *i32Array;

i32Array initi32Array(unsigned int initCapacity);

void pushi32Array(i32Array* target, int item);

void printi32Array(i32Array* target);

void freei32Array(i32Array* target);
/* End i32Array declaration */

/* Start f32Array declaration */
typedef struct f32Array
{
	float* items;
	unsigned int realSize;
	unsigned int capacity;
} *f32Array;

f32Array initf32Array(unsigned int initCapacity);

void pushf32Array(f32Array* target, float item);

void printf32Array(f32Array* target);

void freef32Array(f32Array* target);
/* End f32Array declaration */

/* Start f64Array declaration */
typedef struct f64Array
{
	double* items;
	unsigned int realSize;
	unsigned int capacity;
} *f64Array;

f64Array initf64Array(unsigned int initCapacity);

void pushf64Array(f64Array* target, double item);

void printf64Array(f64Array* target);

void freef64Array(f64Array* target);
/* End f64Array declaration */

/* Start tArray declaration */
typedef struct tArray 
{
	unsigned int realSize;
	unsigned int capacity;
	unsigned char memberSize;
	unsigned char* items;
} *tArray;

tArray initArray(unsigned int initCapacity, unsigned char memberSize);

void expandArray(tArray* target);

void pushArray(tArray* target, void* item);

void getArrayAtIndex(tArray* target, void* outData, unsigned int idx);

void printArray(tArray* target);

void freeArray(tArray* target);

/* End tArray declaration */

#endif // DARRAY_H