#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct stack_t
{
	int top;
	int capacity;
	int memberSize;	
	void* data;
} *stack;

stack initStack(int capacity, int dataSize);
void expandStack(stack* targetPtr);
void pushStack(stack* targetPtr, void* inData);
void topStack(stack* targetPtr, void* outData);
void popStack(stack* targetPtr, void* outData);
void freeStack(stack* targetPtr);

#endif