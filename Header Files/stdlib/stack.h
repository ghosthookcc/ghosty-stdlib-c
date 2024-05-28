#ifndef STACK_H
#define STACK_H

#include <stdio.h>

typedef struct stack_t
{
	int top;
	int capacity;
	int memberSize;	
	void* data;
} *stack;

stack initStack(int capacity, int dataSize);
void expandStack(stack* targetPtr);
void pushStack(stack* targetPtr, void* data);
void topStack(stack* targetPtr, void* output);
void freeStack(stack* targetPtr);

#endif