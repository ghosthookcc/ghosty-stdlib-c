#ifndef HASH_H
#define HASH_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FNV1A_32_HASH_PRIME ((unsigned int)0x01000193u)
#define FNV1A_32_HASH_INIT ((unsigned int)0x811c9dc5u)

typedef struct bucket_t
{
    unsigned int hash;
    unsigned int size;
} bucket;

bucket initHashBucket(unsigned int hash);

unsigned int murmur32Hash(const void* key, unsigned int keyLength, unsigned int seed);
unsigned int fnv1AHash(const void* key, unsigned int keyLength, unsigned int seed);

#endif
