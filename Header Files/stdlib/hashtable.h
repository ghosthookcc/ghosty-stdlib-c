#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <sys/types.h>

#include "hash.h"
#include "linkedList.h"
#include "boolean.h"

#define unsignedIntEqual UnsignedIntEqual

typedef boolean(*equalCallback)(void* data, void* otherData);

typedef struct hashTableBucket_t
{
    bucket _bucket;
    void* data;
} *hashTableBucket;

typedef struct keyPair_t
{
    void* key;
    void* value;
    unsigned int keyLength;
    equalCallback equal;
} *keyPair;

// Speed linear with load factor
typedef struct chainedHashTable_t
{
    //hashTableBucket* buckets;
    linkedList* chains;
    unsigned int entryCount;
    unsigned int capacity;
} *chainedHashTable;

// Speed under low load factor
typedef struct addressedHashTable_t
{

} *openHashTable;

chainedHashTable initChainedHashTable(unsigned int capacity);

keyPair insertIntoChainedHashTable(chainedHashTable* targetPtr, void* key, void* value, unsigned int keyLength, equalCallback equal);
keyPair searchChainedHashTable(chainedHashTable targetPtr, keyPair searchForKeyPair);

keyPair initKeyPair(void* key, void* value, unsigned int keyLength, equalCallback equal);
hashTableBucket initHashTableBucket(unsigned int hash, void* data);

void freeChainedHashTable(chainedHashTable* targetPtr);

boolean unsignedIntEqual(void* data, void* otherData);

#endif // HASHTABLE_H
