#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <sys/types.h>

#include "hash.h"
#include "linkedList.h"
#include "boolean.h"

#define unsignedIntEqual UnsignedIntEqual

typedef boolean(*equalCallback)(void* data, void* otherData);

typedef struct keyPair_t
{
    void* key;
    void* value;
    unsigned int keyLength;
    equalCallback equal;
} *keyPair;

typedef struct chainedHashTableBucket_t
{
    bucket _bucket;
    void* data;
} *chainedHashTableBucket;

typedef struct openHashTableBucket_t 
{
    bucket _bucket;
    keyPair data;
} *openHashTableBucket;

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
    openHashTableBucket*  buckets;
    unsigned int entryCount;
    unsigned int capacity;   
} *openHashTable;

chainedHashTable initChainedHashTable(unsigned int capacity);

keyPair insertIntoChainedHashTable(chainedHashTable* targetPtr, void* key, void* value, unsigned int keyLength, equalCallback equal);
keyPair searchChainedHashTable(chainedHashTable targetPtr, keyPair searchForKeyPair);

chainedHashTableBucket initChainedHashTableBucket(unsigned int hash, void* data);

void freeChainedHashTable(chainedHashTable* targetPtr);

openHashTable initOpenHashTable(unsigned int capacity);

keyPair insertIntoOpenHashTable(openHashTable* targetPtr, void* key, void* value, unsigned int keyLength, equalCallback equal);
keyPair searchOpenHashTable(openHashTable targetPtr, keyPair searchForKeyPair);

openHashTableBucket initOpenHashTableBucket(unsigned int hash, keyPair data);

keyPair initKeyPair(void* key, void* value, unsigned int keyLength, equalCallback equal);

boolean unsignedIntEqual(void* data, void* otherData);

#endif // HASHTABLE_H
