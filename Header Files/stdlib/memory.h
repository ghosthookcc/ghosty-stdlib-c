#ifndef MEMORY_H
#define MEMORY_H

#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct arena_t
{
	size_t storageSizeInBytes;
	size_t realStorageSizeInBytes;
	void* startOffsetInMemory;
	void* lastInsertInMemory;
	void* endOffsetInMemory;
	unsigned char* storage;
	struct arena_t* parent;
} arena;

arena initArena(size_t storageSizeInBytes);
arena initArenaFromArena(arena* other, size_t storageSizeInBytes);

void insertIntoArena(arena targetPtr, void* data, size_t dataLength);
void getArenaAtIndex(arena targetPtr, void* out, unsigned int idx, size_t size);

void freeArena(arena* targetPtr);

#endif // MEMORY_H