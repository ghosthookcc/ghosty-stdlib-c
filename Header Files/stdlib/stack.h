#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Stacks operate with LIFO (Last In First Out)
typedef struct stack_t
{
	unsigned int top;
	unsigned int capacity;
	unsigned int memberSize;	
	unsigned char* data;
} *stack;

stack initStack(unsigned int capacity, unsigned int dataSize);
void expandStack(stack* targetPtr);
void pushStack(stack* targetPtr, void* inData);
void popStack(stack* targetPtr, void* outData);
void peekStack(stack* targetPtr, void* outData);
void freeStack(stack* targetPtr);

#endif // STACK_H