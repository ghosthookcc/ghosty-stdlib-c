#ifndef BIT_H
#define BIT_H

#include <string.h>

unsigned char extractBit(unsigned char byte, size_t position);
unsigned char extractBits(unsigned char byte, size_t startPosition, size_t endPosition);

const char* byteToBinary(unsigned char x);

#endif
