#include "../../Header Files/stdlib/dArray.h"

/* Start i32Array definition */
i32Array initi32Array(unsigned int capacity)
{
	i32Array newi32Array = (i32Array)malloc(sizeof(*newi32Array) + (sizeof(int) * capacity));
	
	newi32Array->items = (int*)calloc(capacity, sizeof(int));
	newi32Array->realSize = 0;
	newi32Array->capacity = capacity;

	return(newi32Array);
}	

void expandi32Array(i32Array* targetPtr)
{
	i32Array dtarget = *targetPtr;
	dtarget->capacity = dtarget->capacity * 2 + 1;
	dtarget->items = realloc(dtarget->items, sizeof(int) * dtarget->capacity);
}

void pushi32Array(i32Array* targetPtr, int item)
{
	i32Array dtarget = *targetPtr;
	if (dtarget->realSize == dtarget->capacity) expandi32Array(targetPtr);

	dtarget->items[dtarget->realSize] = item;
	dtarget->realSize++;
}

void printi32Array(i32Array* targetPtr)
{
	printf("\n");
	i32Array dtarget = *targetPtr;
	for (unsigned int idx = 0; idx < dtarget->realSize; idx++)
	{
		printf("%d ", dtarget->items[idx]);
	}
	printf("\n");
}

void freei32Array(i32Array* targetPtr)
{
	i32Array dtarget = *targetPtr;
	free(dtarget->items);
	dtarget->items = NULL;
	dtarget->realSize = dtarget->capacity = 0;
	free(dtarget);
}
/* End i32Array definition */

/* Start f32Array definition */
f32Array initf32Array(unsigned int capacity)
{
	f32Array newf32Array = (f32Array)malloc(sizeof(*newf32Array) + (sizeof(float) * capacity));
	
	newf32Array->items = (float*)malloc(sizeof(float) * capacity);
	newf32Array->realSize = 0;
	newf32Array->capacity = capacity;

	return(newf32Array);
}	

void expandf32Array(f32Array* targetPtr)
{
	f32Array dtarget = *targetPtr;
	dtarget->capacity = dtarget->capacity * 2 + 1;
	dtarget->items = realloc(dtarget->items, sizeof(float) * dtarget->capacity);	
}

void pushf32Array(f32Array* targetPtr, float item)
{
	f32Array dtarget = *targetPtr;
	if (dtarget->realSize == dtarget->capacity) expandf32Array(targetPtr);

	dtarget->items[dtarget->realSize] = item;
	dtarget->realSize++;
}

void printf32Array(f32Array* targetPtr)
{
	printf("\n");
	f32Array dtarget = *targetPtr;
	for (unsigned int idx = 0; idx < dtarget->realSize; idx++)
	{
		printf("%f ", dtarget->items[idx]);
	}
	printf("\n");
}

void freef32Array(f32Array* targetPtr)
{
	f32Array dtarget = *targetPtr;
	free(dtarget->items);
	dtarget->items = NULL;
	dtarget->realSize = dtarget->capacity = 0;
	free(dtarget);
}
/* End f32Array definition */

/* Start f64Array definition */
f64Array initf64Array(unsigned int capacity)
{
	f64Array newf64Array = (f64Array)malloc(sizeof(*newf64Array) + (sizeof(double) * capacity));
	
	newf64Array->items = (double*)malloc(sizeof(double) * capacity);
	newf64Array->realSize = 0;
	newf64Array->capacity = capacity;

	return(newf64Array);
}	

void expandf64Array(f64Array* targetPtr)
{
	f64Array dtarget = *targetPtr;
	dtarget->capacity = dtarget->capacity * 2 + 1;
	dtarget->items = realloc(dtarget->items, sizeof(double) * dtarget->capacity);
}

void pushf64Array(f64Array* targetPtr, double item)
{
	f64Array dtarget = *targetPtr;
	if (dtarget->realSize == dtarget->capacity) expandf64Array(targetPtr);

	dtarget->items[dtarget->realSize] = item;
	dtarget->realSize++;
}

void printf64Array(f64Array* targetPtr)
{
	printf("\n");
	f64Array dtarget = *targetPtr;
	for (unsigned int idx = 0; idx < dtarget->realSize; idx++)
	{
		printf("%f ", dtarget->items[idx]);
	}
	printf("\n");
}

void freef64Array(f64Array* targetPtr)
{
	f64Array dtarget = *targetPtr;
	free(dtarget->items);
	dtarget->items = NULL;
	dtarget->realSize = dtarget->capacity = 0;
	free(dtarget);
}
/* End f64Array definition */

/* Start tArray definition */
tArray initArray(unsigned int capacity, unsigned char memberSize)
{
	tArray newdArray = (tArray)malloc(sizeof(*newdArray) + memberSize * capacity);
	newdArray->realSize = 0;
	newdArray->capacity = capacity;
	newdArray->memberSize = memberSize;
	newdArray->items = (unsigned char*)calloc(capacity, memberSize);
	return newdArray;
}

void expandArray(tArray* targetPtr)
{
	tArray dtarget = *targetPtr;
	dtarget->capacity = dtarget->capacity * 2 + 1;
	dtarget->items = realloc(dtarget->items, dtarget->memberSize * dtarget->capacity);
}

void pushArray(tArray* targetPtr, void* item)
{
	tArray dtarget = *targetPtr;

	int newSizeIdx = dtarget->realSize+1; 
	if (newSizeIdx > dtarget->capacity) expandArray(targetPtr);

	void* targetDestinationInMemory = (unsigned char*)dtarget->items+(dtarget->memberSize * dtarget->realSize);
	memcpy(targetDestinationInMemory, item, dtarget->memberSize);
	dtarget->realSize = newSizeIdx;
}

void getArrayAtIndex(tArray* targetPtr, void* outData, unsigned int idx)
{
	tArray dtarget = *targetPtr;
	if (idx >= 0 && idx < dtarget->capacity)
	{
		void* targetSourceInMemory = (unsigned char*)dtarget->items+(dtarget->memberSize * idx);
		memcpy(outData, targetSourceInMemory, dtarget->memberSize);
	}
	outData = NULL;
}

void printArray(tArray* targetPtr)
{
	tArray dtarget = *targetPtr;
}

void freeArray(tArray* targetPtr)
{
	tArray dtarget = *targetPtr;
	free(dtarget->items);
	free(dtarget);
}
/* End tArray definition */