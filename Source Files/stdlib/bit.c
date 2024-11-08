#include "../../Header Files/stdlib/bit.h"

// Start counting from right to left, 0 indexed
unsigned char extractBit(unsigned char byte, size_t position)
{
    return (byte >> position) & 0x01;
}

// Start counting from left to right, 0 indexed
// End is inclusive
unsigned char extractBits(unsigned char byte, size_t startPosition, size_t endPosition)
{
    unsigned char mask = 0;
    for (size_t bit = startPosition; bit <= endPosition; bit++)
    {
        mask = mask | (1 << bit);
    }
    return (byte & mask) >> startPosition;
}

const char* byteToBinary(unsigned char x)
{
    static char b[9];
    b[0] = '\0';

    size_t z;
    for (z = 128; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}
