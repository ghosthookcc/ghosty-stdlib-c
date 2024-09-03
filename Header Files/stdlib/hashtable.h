#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "hash.h"
#include "linkedList.h"

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
void insertIntoChainedHashTable(chainedHashTable* targetPtr, keyPair keyPair);
keyPair searchChainedHashTable(chainedHashTable targetPtr, keyPair keyPair);

keyPair initKeyPair(void* key, void* value, unsigned int keyLength);
hashTableBucket initHashTableBucket(unsigned int hash, void* data);

#endif // HASHTABLE_H
