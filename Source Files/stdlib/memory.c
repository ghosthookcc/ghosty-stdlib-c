#include "../../Header Files/stdlib/memory.h"

arena initArena(size_t storageSizeInBytes)
{
	arena newArena;
	newArena.storageSizeInBytes = storageSizeInBytes;
	newArena.realStorageSizeInBytes = 0;

	newArena.storage = aligned_alloc(1024, storageSizeInBytes);
	memset(newArena.storage, ~((unsigned int)0), storageSizeInBytes);

	newArena.startOffsetInMemory = newArena.storage;
	newArena.lastInsertInMemory = newArena.startOffsetInMemory;
	newArena.endOffsetInMemory = newArena.storage + storageSizeInBytes;

	newArena.parent = NULL;
	
	return newArena;
}

arena initArenaFromArena(arena* other, size_t storageSizeInBytes)
{
	if (storageSizeInBytes >= other->storageSizeInBytes) return *other;

	arena newArena;
	newArena.storageSizeInBytes = storageSizeInBytes;
	newArena.realStorageSizeInBytes = 0;
	
	void* otherArenaNewMemoryEndOffset = &other->endOffsetInMemory - storageSizeInBytes;
	
	newArena.startOffsetInMemory = otherArenaNewMemoryEndOffset;
	newArena.lastInsertInMemory = newArena.startOffsetInMemory;
	newArena.endOffsetInMemory = &otherArenaNewMemoryEndOffset + storageSizeInBytes;

	newArena.storage = otherArenaNewMemoryEndOffset;
	
	newArena.parent = other;

	other->storageSizeInBytes -= storageSizeInBytes;
	other->endOffsetInMemory = otherArenaNewMemoryEndOffset;

	return newArena;
}

void insertIntoArena(arena targetPtr, void* data, size_t dataLength)
{
	if (targetPtr.realStorageSizeInBytes + dataLength > targetPtr.storageSizeInBytes) return;
	printf("\n\n%p\n\n", data);
	memcpy(targetPtr.lastInsertInMemory, data, dataLength);
	targetPtr.lastInsertInMemory = (unsigned char*)targetPtr.lastInsertInMemory+dataLength;
}

void getArenaAtIndex(arena targetPtr, void* out, unsigned int idx, size_t size)
{
	memcpy(out, (unsigned char*)targetPtr.storage+(idx * size), size);
}

void freeArena(arena* targetPtr)
{
	arena dtarget = *targetPtr;
	if (dtarget.parent == NULL) 
	{ 
		free(dtarget.storage); 
	}
}