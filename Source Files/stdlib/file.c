#include "../../Header Files/stdlib/file.h"

FILE* openFile(string filePath, const char* fileMode, long int offset)
{
	FILE* fileHandle = fopen(filePath->chars, fileMode);
	fseek(fileHandle, offset, SEEK_SET);
	return(fileHandle);
}

char readNext(FILE* fileHandle)
{
	char next = fgetc(fileHandle);
	return(next);
}

char* readNextBy(FILE* fileHandle, int amount)
{
	char* content = (char*)malloc( ( sizeof(char) * amount ) + 1);

	int nextCharIdx = -1;
	while (!feof(fileHandle) && nextCharIdx < amount)
	{
		nextCharIdx++; 
		content[nextCharIdx] = readNext(fileHandle);
	}
	content[nextCharIdx] = '\0';

	return(content);
} 

char* readAll(FILE* fileHandle)
{
	long int savedFileOffset = ftell(fileHandle);
	rewind(fileHandle);
	
	char* content = readRemaining(fileHandle);
	fseek(fileHandle, savedFileOffset, SEEK_SET);

	return(content);
}

char* readRemaining(FILE* fileHandle)
{
	long int contentLength = tellRemaining(fileHandle);
	char* content = (char*)malloc( ( sizeof(char) * contentLength ) + 1);

	char nextSymbol;
	int nextSymbolIdx = -1;
	while (!feof(fileHandle))
	{
		nextSymbolIdx++;
		nextSymbol = readNext(fileHandle);
		content[nextSymbolIdx] = nextSymbol;
	}
	content[nextSymbolIdx] = '\0';

	return(content);
}

long int tellRemaining(FILE* fileHandle)
{	
	long int remainingLength = tellSize(fileHandle) - ftell(fileHandle);
	return(remainingLength);
}

long int tellSize(FILE* fileHandle)
{
	long int savedFileOffset = ftell(fileHandle);
	fseek(fileHandle, 0L, SEEK_END);
	long int size = ftell(fileHandle);
	fseek(fileHandle, savedFileOffset, SEEK_SET);
	return(size);
}
