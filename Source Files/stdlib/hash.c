#include "../../Header Files/stdlib/hash.h"


unsigned int murmur32Hash(const char* key, unsigned int keyLength, unsigned int seed)
{
    unsigned int c1 = 0xcc9e2d51;
    unsigned int c2 = 0x1b873593;
    unsigned int r1 = 15;
    unsigned int r2 = 13;
    unsigned int m = 5;
    unsigned int n = 0xe6546b64;
    unsigned int hash = 0;
    unsigned int currentOctet = 0;
    unsigned char* d = (unsigned char*)key;

    const unsigned int* chunks;
    const unsigned char* tail;

    int idx = 0;
    int length = keyLength / 4;

    hash = seed;

    chunks = (const unsigned int*)(d + length * 4);
    tail   = (const unsigned char*)(d + length * 4);

    for (idx = -length; idx != 0; idx++)
    {
        currentOctet = chunks[idx];

        currentOctet *= c1;
        currentOctet = (currentOctet << r1) | (currentOctet >> (32 - r1));
        currentOctet *= c2;

        hash ^= currentOctet;
        hash = (currentOctet << r2) | (hash >> (32 - r2));
        hash = hash * m + n;
    }

    currentOctet = 0;

    switch (keyLength & 3)
    {
        case 3: currentOctet ^= (tail[2] << 16);
        case 2: currentOctet ^= (tail[1] << 8);
        case 1:
            currentOctet ^= tail[0];
            currentOctet *= c1;
            currentOctet = (currentOctet << r1) | (currentOctet >> (32 - r1));
            currentOctet *= c2;
            hash ^= currentOctet;
    }

    hash ^= keyLength;

    hash ^= (hash >> 16);
    hash *= 0x85ebca6b;
    hash ^= (hash >> 13);
    hash *= 0xc2b2ae35;
    hash ^= (hash >> 16);

    return hash;
}
