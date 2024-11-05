#ifndef DARRAY_H
#define DARRAY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "string.h"

/* Start i32Array declaration */
typedef struct i32Array
{
	unsigned int realSize;
	unsigned int capacity;
	int* items;
} *i32Array;

i32Array initi32Array(unsigned int capacity);

void exapndi32Array(i32Array* targetPtr);

void pushi32Array(i32Array* targetPtr, int item);

void freei32Array(i32Array* targetPtr);
/* End i32Array declaration */

/* Start f32Array declaration */
typedef struct f32Array
{
	unsigned int realSize;
	unsigned int capacity;
	float* items;
} *f32Array;

f32Array initf32Array(unsigned int capacity);

void expandf32Array(f32Array* targetPtr);

void pushf32Array(f32Array* targetPtr, float item);

void freef32Array(f32Array* targetPtr);
/* End f32Array declaration */

/* Start f64Array declaration */
typedef struct f64Array
{
	unsigned int realSize;
	unsigned int capacity;
	double* items;
} *f64Array;

f64Array initf64Array(unsigned int capacity);

void expandf64Array(f64Array* targetPtr);

void pushf64Array(f64Array* targetPtr, double item);

void freef64Array(f64Array* targetPtr);
/* End f64Array declaration */

/* Start tArray declaration */
typedef struct tArray 
{
	unsigned int realSize;
	unsigned int capacity;
	unsigned char memberSize;
	unsigned char* items;
} *tArray;

tArray initArray(unsigned int capacity, unsigned char memberSize);

void expandArray(tArray* targetPtr);

void pushArray(tArray* targetPtr, void* item);

void getArrayAtIndex(tArray* targetPtr, void* outData, unsigned int idx);

void freeArray(tArray* targetPtr);

/* End tArray declaration */

#endif // DARRAY_H