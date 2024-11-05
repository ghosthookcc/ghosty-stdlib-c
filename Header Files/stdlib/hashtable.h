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

#define unsignedIntEqual UnsignedIntEqual

typedef boolean(*equalCallback)(void* data, void* otherData);

typedef struct keyPair_t
{
    void* key;
    void* value;
} *keyPair;

typedef struct entryKey_t
{
    unsigned int hash;
    void* key;
} entryKey;

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
} openHashTable;

openHashTable initOpenHashTable(equalCallback equal, size_t keySize, size_t valueSize);

void* insertIntoOpenHashTable(openHashTable* targetPtr, 
                              void* key, void* value);
keyPair searchOpenHashTable(openHashTable* targetPtr, void* key);

void freeOpenHashTable(openHashTable* targetPtr);

keyPair initKeyPair(void* key, void* value, 
                    size_t keyLength, size_t valueLength);

boolean unsignedIntEqual(void* data, void* otherData);

#endif // HASHTABLE_H