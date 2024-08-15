#ifndef HASH_H
#define HASH_H

typedef struct bucket_t
{
    unsigned int hash;
    unsigned int size;
} bucket;

unsigned int murmur32Hash(const char* key, unsigned int keyLength, unsigned int seed);


#endif
