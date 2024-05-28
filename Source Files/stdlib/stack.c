#include "../../Header Files/stdlib/stack.h"

// Stacks operate with LIFO (Last In First Out)

stack initStack(int capacity, int dataSize)
{
	stack newStack = (stack)malloc(sizeof(*newStack) + (capacity * dataSize));
	newStack->top = 0;
	newStack->capacity = capacity;
	newStack->memberSize = dataSize;
	newStack->data = (char*)malloc(dataSize * capacity);
	return newStack;
}

void expandStack(stack* targetPtr)
{
	stack dtarget = *targetPtr;
	dtarget->capacity = dtarget->capacity * 2 + 1;
	dtarget->data = (char*)realloc(dtarget->data, dtarget->memberSize * dtarget->capacity);
}

void pushStack(stack* targetPtr, void* inData)
{
	stack dtarget = *targetPtr;
	int newTopIdx = dtarget->top+1;
	if (newTopIdx > dtarget->capacity) expandStack(targetPtr);

	void* targetDestinationInMemory = (char*)dtarget->data+(dtarget->memberSize*newTopIdx);
	memcpy(targetDestinationInMemory, inData, dtarget->memberSize);
	dtarget->top = newTopIdx;
}

void popStack(stack* targetPtr, void* outData)
{
	stack dtarget = *targetPtr;
	if (dtarget->top <= 0) return;
	int newTopIdx = dtarget->top-1;

	void* targetDestinationInMemory = (char*)dtarget->data+(dtarget->memberSize*dtarget->top);
	memcpy(outData, targetDestinationInMemory, dtarget->memberSize);
	dtarget->top = newTopIdx;
}

void topStack(stack* targetPtr, void* outData)
{
	stack dtarget = *targetPtr;
	if (dtarget->top <= 0) return;

	void* topDestinationInMemory = (char*)dtarget->data+(dtarget->memberSize*dtarget->top);
	memcpy(outData, topDestinationInMemory, dtarget->memberSize);
}

void freeStack(stack* targetPtr)
{
	stack dtarget = *targetPtr;
	free(dtarget->data);
	free(dtarget);
}