#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "hash.h"
#include "linkedList.h"

typedef struct hashTableBucket_t
{
    bucket bucket;
    linkedList data;
} hashTableBucket;

// Speed linear with load factor
typedef struct chainedHashTable_t
{

} *chainedHashTable;

// Speed under low load factor
typedef struct addressedHashTable_t
{

} *openHashTable;

#endif // HASHTABLE_H
