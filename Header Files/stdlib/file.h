#ifndef FILE_H
#define FILE_H

#include <stdlib.h>
#include <stdio.h>

FILE* openFile(char* filePath, const char* fileMode, long int offset);

char readNext(FILE* file);
char* readNextChars(FILE* file, int amount);
char* readAll(FILE* file);
char* readRemaining(FILE* file);

long int tellRemaining(FILE* file);
long int tellSize(FILE* file);

#endif // FILE_H