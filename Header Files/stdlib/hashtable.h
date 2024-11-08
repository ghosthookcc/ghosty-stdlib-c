#ifndef hashTable_H
#define hashTable_H

#include <sys/types.h>
#include <string.h>

#include "common.h"
#include "hash.h"
#include "linkedList.h"
#include "boolean.h"
#include "dArray.h"
#include "memory.h"

#define BYTESINMB 1000000

#define unsignedIntEqual UnsignedIntEqual

typedef boolean(*equalCallback)(void* data, void* otherData);

typedef struct keyPair_t
{
    void* key;
    void* value;
} *keyPair;

typedef struct hashTable_t
{
    unsigned int capacity;
    unsigned int entryCount;
    
    size_t keySize;
    size_t valueSize; 
    size_t hashSize;
    size_t keyEntrySize;

    equalCallback equal;

    arena keys;
    arena values;
} *hashTable;

hashTable initHashTable(equalCallback equal, 
                                size_t keySize, size_t valueSize,
                                size_t sizeInMb, size_t alignment);

void* insertIntoHashTable(hashTable targetPtr, 
                              void* key, void* value);
keyPair searchHashTable(hashTable targetPtr, void* key);

void freeHashTable(hashTable targetPtr);

keyPair initKeyPair(void* key, void* value,
                    size_t keySize, size_t valueSize);

void freeKeyPair(keyPair targetPtr);

boolean unsignedIntEqual(void* data, void* otherData);

#endif // hashTable_H
