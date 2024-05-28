#include "../../Header Files/stdlib/dArray.h"

/* Start i32Array definition */

i32Array* initI32Array(unsigned int initCapacity)
{
	i32Array* new = malloc(sizeof(*new) + (sizeof(int) * initCapacity));
	
	new->items = malloc(sizeof(int) * initCapacity);
	new->realSize = 0;
	new->capacity = initCapacity;

	return(new);
}	

void pushI32(i32Array** target, int item)
{
	i32Array* targetDerefed = *target;
	if ( targetDerefed->realSize == targetDerefed->capacity )
	{
		// Grow target array by 2k+1
		targetDerefed->capacity = targetDerefed->capacity * 2 + 1;
		targetDerefed->items = realloc(targetDerefed->items, sizeof(int) * targetDerefed->capacity);
	}
	targetDerefed->items[targetDerefed->realSize] = item;
	targetDerefed->realSize++;
}

void printI32Array(i32Array** target)
{
	printf("\n");
	i32Array* targetDerefed = *target;
	for (unsigned int idx = 0; idx < targetDerefed->realSize; idx++)
	{
		printf("%d ", targetDerefed->items[idx]);
	}
	printf("\n");
}

void freeI32Array(i32Array** target)
{
	i32Array* targetDerefed = *target;
	free(targetDerefed->items);
	targetDerefed->items = NULL;
	targetDerefed->realSize = targetDerefed->capacity = 0;
	free(targetDerefed);
}

/* End i32Array definition */

/* Start f32Array definition */

f32Array* initF32Array(unsigned int initCapacity)
{
	f32Array* new = malloc(sizeof(*new) + (sizeof(float) * initCapacity));
	
	new->items = malloc(sizeof(float) * initCapacity);
	new->realSize = 0;
	new->capacity = initCapacity;

	return(new);
}	

void pushF32(f32Array** target, float item)
{
	f32Array* targetDerefed = *target;
	if ( targetDerefed->realSize == targetDerefed->capacity )
	{
		// Grow target array by 2k+1
		targetDerefed->capacity = targetDerefed->capacity * 2 + 1;
		targetDerefed->items = realloc(targetDerefed->items, sizeof(float) * targetDerefed->capacity);
	}
	targetDerefed->items[targetDerefed->realSize] = item;
	targetDerefed->realSize++;
}

void printF32Array(f32Array** target)
{
	printf("\n");
	f32Array* targetDerefed = *target;
	for (unsigned int idx = 0; idx < targetDerefed->realSize; idx++)
	{
		printf("%f ", targetDerefed->items[idx]);
	}
	printf("\n");
}

void freeF32Array(f32Array** target)
{
	f32Array* targetDerefed = *target;
	free(targetDerefed->items);
	targetDerefed->items = NULL;
	targetDerefed->realSize = targetDerefed->capacity = 0;
	free(targetDerefed);
}

/* End f32Array definition */

/* Start f64Array definition */

f64Array* initF64Array(unsigned int initCapacity)
{
	f64Array* new = malloc(sizeof(*new) + (sizeof(double) * initCapacity));
	
	new->items = malloc(sizeof(double) * initCapacity);
	new->realSize = 0;
	new->capacity = initCapacity;

	return(new);
}	

void pushF64(f64Array** target, double item)
{
	f64Array* targetDerefed = *target;
	if ( targetDerefed->realSize == targetDerefed->capacity )
	{
		// Grow target array by 2k+1
		targetDerefed->capacity = targetDerefed->capacity * 2 + 1;
		targetDerefed->items = realloc(targetDerefed->items, sizeof(double) * targetDerefed->capacity);
	}
	targetDerefed->items[targetDerefed->realSize] = item;
	targetDerefed->realSize++;
}

void printF64Array(f64Array** target)
{
	printf("\n");
	f64Array* targetDerefed = *target;
	for (unsigned int idx = 0; idx < targetDerefed->realSize; idx++)
	{
		printf("%f ", targetDerefed->items[idx]);
	}
	printf("\n");
}

void freeF64Array(f64Array** target)
{
	f64Array* targetDerefed = *target;
	free(targetDerefed->items);
	targetDerefed->items = NULL;
	targetDerefed->realSize = targetDerefed->capacity = 0;
	free(targetDerefed);
}

/* End f64Array definition */