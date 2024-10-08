#include "../../Header Files/stdlib/stack.h"

// Stacks operate with LIFO (Last In First Out)
stack initStack(unsigned int capacity, unsigned int memberSize)
{
	stack newStack = (stack)malloc(sizeof(*newStack) + memberSize * capacity);
	newStack->top = 0;
	newStack->capacity = capacity;
	newStack->memberSize = memberSize;
	newStack->data = (unsigned char*)malloc(memberSize * capacity);
	return newStack;
}

void expandStack(stack* targetPtr)
{
	stack dtarget = *targetPtr;
	dtarget->capacity = dtarget->capacity * 2 + 1;
	dtarget->data = realloc(dtarget->data, dtarget->memberSize * dtarget->capacity);
}

void pushStack(stack* targetPtr, void* inData)
{
	stack dtarget = *targetPtr;
	int newTopIdx = dtarget->top + 1;
	if (newTopIdx > dtarget->capacity) expandStack(targetPtr);

	void* targetDestinationInMemory = (unsigned char*)dtarget->data+(dtarget->memberSize * dtarget->top);
	memcpy(targetDestinationInMemory, inData, dtarget->memberSize);

	dtarget->top = newTopIdx;
}

void popStack(stack* targetPtr, void* outData)
{
	stack dtarget = *targetPtr;
	if (dtarget->top == 0) return;
	int newTopIdx = dtarget->top-1;

	void* sourceDestinationInMemory = (unsigned char*)dtarget->data+(dtarget->memberSize * (dtarget->top-1));
	memcpy(outData, sourceDestinationInMemory, dtarget->memberSize);

	dtarget->top = newTopIdx;
}

void peekStack(stack* targetPtr, void* outData)
{
	stack dtarget = *targetPtr;
	if (dtarget->top == 0) return;

	void* topDestinationInMemory = (unsigned char*)dtarget->data+(dtarget->memberSize * (dtarget->top-1));
	memcpy(outData, topDestinationInMemory, dtarget->memberSize);
}

void freeStack(stack* targetPtr)
{
	stack dtarget = *targetPtr;
	free(dtarget->data);
	free(dtarget);
}