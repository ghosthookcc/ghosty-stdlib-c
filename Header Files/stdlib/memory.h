#ifndef MEMORY_H
#define MEMORY_H

#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#define ARENAENTRYTAKEN ((unsigned int)~0)

#ifndef MEMORYMACROS
#define MEMORYMACROS
    #if defined(__linux__)
    #define gsalignedAlloc(alignment,size) (aligned_alloc(alignment, size))
    #define gsalignedFree(block) (free(block))
    #elif defined (_WIN32)
    #define gsalignedAlloc(alignment,size) (_aligned_malloc(size, alignment))
    #define gsalignedFree(block) (_aligned_free(block))
    #endif
#endif

typedef struct arena_t
{
	size_t storageSizeInBytes;
	size_t realStorageSizeInBytes;
	struct arena_t* parent;
    unsigned char* startOffsetInMemory;
	unsigned char* endOffsetInMemory;
	unsigned char* lastInsertInMemory;
	unsigned char* storage;
} *arena;

arena initArena(size_t storageSizeInBytes, size_t alignment);
arena initArenaFromArena(arena other, size_t storageSizeInBytes);

void insertIntoArena(arena targetPtr, void* data, size_t dataLength, size_t offset, unsigned int idx);

void getArenaAtIndex(arena targetPtr, void* out, unsigned int idx, size_t size);
void* getArenaMemoryAtIndex(arena targetPtr, unsigned int idx, size_t size);

void freeArena(arena targetPtr);

void gsmemset(void* destination, size_t setSize, int setTo);

#endif // MEMORY_H
