#include "../../Header Files/stdlib/queue.h"

// Queues operate with FIFO (First In First Out)
queue initQueue(unsigned int capacity, unsigned int memberSize)
{
	queue newQueue = (queue)malloc(sizeof(*newQueue) +  memberSize * capacity);
	newQueue->realSize = 0;
	newQueue->capacity = capacity;
	newQueue->memberSize = memberSize;
	newQueue->data = (unsigned char*)malloc(memberSize * capacity);
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
	int newSizeIdx = dtarget->realSize+1; 
	if (newSizeIdx > dtarget->capacity) expandQueue(targetPtr);

	void* targetDestinationInMemory = (unsigned char*)dtarget->data+(dtarget->memberSize * dtarget->realSize);
	memcpy(targetDestinationInMemory, inData, dtarget->memberSize);
	dtarget->realSize = newSizeIdx;
}

void dequeueQueue(queue* targetPtr, void* outData)
{
	queue dtarget = *targetPtr;
	if (dtarget->realSize == 0) return;
	int newSizeIdx = dtarget->realSize-1;

	void* sourceDestinationInMemory = (unsigned char*)dtarget->data;
	memcpy(outData, sourceDestinationInMemory, dtarget->memberSize);

	void* frontDestinationInMemory;
	void* rearDestinationInMemory;
	for (int idx = 0; idx < newSizeIdx; idx++)
	{		
		frontDestinationInMemory = (unsigned char*)dtarget->data+(dtarget->memberSize * idx);
		rearDestinationInMemory = (unsigned char*)dtarget->data+(dtarget->memberSize * (idx+1));
		memcpy(frontDestinationInMemory, rearDestinationInMemory, dtarget->memberSize);
	}
	dtarget->realSize = newSizeIdx;
}

void peekQueue(queue* targetPtr, void* outData)
{
	queue dtarget = *targetPtr;
	if (dtarget->realSize == 0) return;

	void* sourceDestinationInMemory = (unsigned char*)dtarget->data;
	memcpy(outData, sourceDestinationInMemory, dtarget->memberSize);
} 

void freeQueue(queue* targetPtr)
{
	queue dtarget = *targetPtr;
	free(dtarget->data);
	free(dtarget);
}
