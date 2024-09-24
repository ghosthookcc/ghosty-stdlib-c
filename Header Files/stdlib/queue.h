#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Queues operate with FIFO (First In First Out)
typedef struct queue_t
{
	unsigned int realSize;
	unsigned int memberSize;
	unsigned int capacity;
	unsigned char* data;
} *queue;

queue initQueue(unsigned int capacity, unsigned int dataSize);
void expandQueue(queue* targetPtr);
void enqueueQueue(queue* targetPtr, void* inData);
void dequeueQueue(queue* targetPtr, void* outData);
void peekQueue(queue* targetPtr, void* outData);
void freeQueue(queue* targetPtr);

#endif // QUEUE_H