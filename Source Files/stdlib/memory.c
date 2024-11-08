#include "../../Header Files/stdlib/memory.h"

arena initArena(size_t storageSizeInBytes, size_t alignment)
{
	arena newArena = malloc(sizeof(*newArena));
	newArena->storageSizeInBytes = storageSizeInBytes;
	newArena->realStorageSizeInBytes = 0;

	newArena->storage = aligned_alloc(alignment, storageSizeInBytes);

    if (newArena->storage == NULL || ((uintptr_t)newArena->storage % alignment) != 0) 
    {
        printf("[-] Memory allocation failed or is misaligned . . .\n");
    }

	memset(newArena->storage, ARENAENTRYTAKEN, storageSizeInBytes);

	newArena->startOffsetInMemory = newArena->storage;
	newArena->endOffsetInMemory = newArena->storage + storageSizeInBytes;
	newArena->lastInsertInMemory = newArena->storage;

	newArena->parent = NULL;
	
	return newArena;
}

arena initArenaFromArena(arena other, size_t storageSizeInBytes)
{
	if (storageSizeInBytes >= other->storageSizeInBytes) return other;

	arena newArena = malloc(sizeof(*newArena));
	newArena->storageSizeInBytes = storageSizeInBytes;
	newArena->realStorageSizeInBytes = 0;
	
	unsigned char* otherArenaNewMemoryEndOffset = other->endOffsetInMemory - storageSizeInBytes;
	
	newArena->startOffsetInMemory = otherArenaNewMemoryEndOffset;
	newArena->lastInsertInMemory = newArena->startOffsetInMemory;
	newArena->endOffsetInMemory = otherArenaNewMemoryEndOffset + storageSizeInBytes;

	newArena->storage = otherArenaNewMemoryEndOffset;
	
	newArena->parent = other;

	other->storageSizeInBytes -= storageSizeInBytes;
	other->endOffsetInMemory = otherArenaNewMemoryEndOffset;

	return newArena;
}

void insertIntoArena(arena targetPtr, void* data, size_t dataLength, size_t offset, unsigned int idx)
{
	if (targetPtr->realStorageSizeInBytes + dataLength > targetPtr->storageSizeInBytes) return;	

    if (idx != ARENAENTRYTAKEN)
    {
    	unsigned char* destination = targetPtr->storage+offset+(idx*dataLength);
 		memcpy(destination, data, dataLength);
    }
    else 
    {
        memcpy(targetPtr->lastInsertInMemory, data, dataLength);
        targetPtr->lastInsertInMemory += dataLength;
    }
    targetPtr->realStorageSizeInBytes += dataLength; 
}

void getArenaAtIndex(arena targetPtr, void* out, unsigned int idx, size_t size)
{
	memcpy(out, targetPtr->storage+(idx * size), size);
}

void* getArenaMemoryAtIndex(arena targetPtr, unsigned int idx, size_t size)
{
    return targetPtr->storage+(idx * size);
}

void freeArena(arena targetPtr)
{
    if (targetPtr->parent == NULL)
    {
        free(targetPtr->storage); 
    }
    free(targetPtr);
}

void gsmemset(void* destination, size_t setSize, int setTo)
{
    unsigned char* memoryStartAddressPtr = destination;
    for (size_t idx = 0; idx < setSize; idx++)
    {
       *memoryStartAddressPtr++ = setTo;
    }
}
