#include "../../Header Files/stdlib/queue.h"

// Queues operate with FIFO (First In First Out)
queue initQueue(unsigned int capacity, unsigned int dataSize)
{
	queue newQueue = (queue)malloc(sizeof(*newQueue) + (capacity * dataSize));
	newQueue->size = 0;
	newQueue->capacity = capacity;
	newQueue->memberSize = dataSize;
	newQueue->data = (unsigned char*)malloc(capacity * dataSize);
	return newQueue;
}

void expandQueue(queue* targetPtr)
{
	queue dtarget = *targetPtr;
	dtarget->capacity = dtarget->capacity * 2 + 1; 
	dtarget->data = realloc(dtarget->data, dtarget->memberSize * dtarget->capacity);
}

void enqueueQueue(queue* targetPtr, void* inData)
{
	queue dtarget = *targetPtr;
	int newSizeIdx = dtarget->size+1; 
	if (newSizeIdx > dtarget->capacity) expandQueue(targetPtr);

	void* targetDestinationInMemory = (unsigned char*)dtarget->data+(dtarget->memberSize*newSizeIdx);
	memcpy(targetDestinationInMemory, inData, dtarget->memberSize);
	dtarget->size = newSizeIdx;
}

void dequeueQueue(queue* targetPtr, void* outData)
{
	queue dtarget = *targetPtr;
	if (dtarget->size == 0) return;
	int newSizeIdx = dtarget->size-1;

	void* sourceDestinationInMemory = (unsigned char*)dtarget->data+(dtarget->memberSize);
	memcpy(outData, sourceDestinationInMemory, dtarget->memberSize);

	void* frontDestinationInMemory;
	void* rearDestinationInMemory;
	for (int idx = 1; idx <= newSizeIdx; idx++)
	{		
		frontDestinationInMemory = (unsigned char*)dtarget->data+(dtarget->memberSize*idx);
		rearDestinationInMemory = (unsigned char*)dtarget->data+(dtarget->memberSize*(idx+1));
		memcpy(frontDestinationInMemory, rearDestinationInMemory, dtarget->memberSize);
	}

	dtarget->size = newSizeIdx;
}

void peekQueue(queue* targetPtr, void* outData)
{
	queue dtarget = *targetPtr;
	if (dtarget->size == 0) return;

	void* sourceDestinationInMemory = (unsigned char*)dtarget->data+(dtarget->memberSize);
	memcpy(outData, sourceDestinationInMemory, dtarget->memberSize);
} 

void freeQueue(queue* targetPtr)
{
	queue dtarget = *targetPtr;
	free(dtarget->data);
	free(dtarget);
}
