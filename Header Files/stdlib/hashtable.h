#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <sys/types.h>
#include <string.h>

#include "common.h"
#include "hash.h"
#include "linkedList.h"
#include "boolean.h"
#include "dArray.h"
#include "memory.h"

#define BYTESINMB 1000000.0

#define unsignedIntEqual UnsignedIntEqual

typedef boolean(*equalCallback)(void* data, void* otherData);

typedef struct keyPair_t
{
    void* key;
    void* value;
} *keyPair;

// Speed under low load factor
typedef struct addressedHashTable_t
{
    unsigned int capacity;
    unsigned int entryCount;
    
    size_t keySize;
    size_t valueSize; 
    size_t hashSize;

    equalCallback equal;

    arena keys;
    arena values;
} *openHashTable;

typedef struct entryKey_t
{
    unsigned int hash;
    void* key;
} entryKey;

openHashTable initOpenHashTable(equalCallback equal, 
                                size_t keySize, size_t valueSize,
                                size_t sizeInMb, size_t alignment);

void* insertIntoOpenHashTable(openHashTable targetPtr, 
                              void* key, void* value);
keyPair searchOpenHashTable(openHashTable targetPtr, void* key);

void freeOpenHashTable(openHashTable targetPtr);

keyPair initKeyPair(void* key, void* value);

boolean unsignedIntEqual(void* data, void* otherData);

#endif // HASHTABLE_H
