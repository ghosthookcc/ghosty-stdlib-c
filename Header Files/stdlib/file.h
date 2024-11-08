#ifndef FILE_H
#define FILE_H

#include <stdlib.h>
#include <stdio.h>

#include "string.h"

FILE* openFile(string filePath, const char* fileMode, long int offset);

char readNext(FILE* fileHandle);
char* readNextChars(FILE* fileHandle, int amount);
char* readAll(FILE* fileHandle);
char* readRemaining(FILE* fileHandle);

long int tellRemaining(FILE* fileHandle);
long int tellSize(FILE* fileHandle);

#endif // FILE_H
