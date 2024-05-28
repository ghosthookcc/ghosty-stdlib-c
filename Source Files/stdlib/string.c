#include "../../Header Files/stdlib/string.h"

/* Start string definition */

string* initString(unsigned int initCapacity)
{
	string* new = malloc(sizeof(*new) + (sizeof(char) * initCapacity));
	
	new->chars = malloc((sizeof(char) * initCapacity) + 1);
	new->realSize = 0;
	new->capacity = initCapacity;

	new->chars[new->realSize] = '\0';

	return(new);
}		

void pushChar(string** target, char item)
{
	string* targetDerefed = *target;
	if ( targetDerefed->realSize == targetDerefed->capacity )
	{
		// Grow target array by 2k+1
		targetDerefed->capacity = targetDerefed->capacity * 2 + 1;
		targetDerefed->chars = realloc(targetDerefed->chars, (sizeof(char) * targetDerefed->capacity) + 1);
	}
	targetDerefed->chars[targetDerefed->realSize] = item;
	targetDerefed->realSize++;			
	targetDerefed->chars[targetDerefed->realSize] = '\0';
}

void pushChars(string** target, char* item)
{
	string* targetDerefed = *target;
	unsigned int itemCharsLen = sizeof(char) * getStringLen(item);
	if ( targetDerefed->realSize + itemCharsLen > targetDerefed->capacity )
	{
		// Grow target array by ((n + strLen) + 2k)+1
		targetDerefed->capacity = (targetDerefed->realSize + itemCharsLen) + (targetDerefed->capacity * 2) + 1;
		targetDerefed->chars = realloc(targetDerefed->chars, sizeof(char) * targetDerefed->capacity);
	}
	for (unsigned int idx = 0; idx < itemCharsLen; idx++)
	{
		targetDerefed->chars[targetDerefed->realSize] = item[idx];
		targetDerefed->realSize++;
	}
	targetDerefed->chars[targetDerefed->realSize] = '\0';
}

void printString(string** target)
{
	printf("\n");
	string* targetDerefed = *target;
	printf("%s ", targetDerefed->chars);
	printf("\n");
}

void freeString(string** target)
{
	string* targetDerefed = *target;
	free(targetDerefed->chars);
	targetDerefed->chars = NULL;
	targetDerefed->realSize = targetDerefed->capacity = 0;
	free(targetDerefed);
}

/* End string definition */

/* Start stringArray definition */

stringArray* initStringArray(unsigned int initCapacity)
{
	stringArray* new = malloc(sizeof(*new) + (sizeof(string) * initCapacity));

	new->items = malloc(sizeof(new->items) * initCapacity);
	new->realSize = 0;
	new->capacity = initCapacity;

	return(new);
}

void pushString(stringArray** target, string* item)
{
	stringArray* targetDerefed = *target;
	if ( targetDerefed->realSize == targetDerefed->capacity )
	{
		// Grow target array by 2k+1
		targetDerefed->capacity = targetDerefed->capacity * 2 + 1;
		targetDerefed->items = realloc(targetDerefed->items, sizeof(string) * targetDerefed->capacity);	
	}
	targetDerefed->items[targetDerefed->realSize] = item;
	targetDerefed->realSize++;
}

void printStringArray(stringArray** target)
{
	printf("\n");
	stringArray* targetDerefed = *target;
	for (unsigned int idx = 0; idx < targetDerefed->realSize; idx++)
	{
		printString(&targetDerefed->items[idx]);
	}
	printf("\n");
}

void freeStringArray(stringArray** target)
{
	stringArray* targetDerefed = *target;
	for (unsigned int idx = 0; idx < targetDerefed->realSize; idx++)
	{
		freeString(&targetDerefed->items[idx]);
	}
	free(targetDerefed->items);
	targetDerefed->items = NULL;
	targetDerefed->realSize = targetDerefed->capacity = 0;
	free(targetDerefed);
}

/* End stringArray definition */

unsigned int getStringLen(char* string)
{
	char* offset = string;
	unsigned int len = 0;
	while (*offset != '\0')
	{
		offset++;
		len++;
	}
	return(len);
}

unsigned char stringEndsWith(char* string, char checkForChar)
{
	unsigned char endsWithChar = 0;
	unsigned int stringLen = getStringLen(string);
	if (string[stringLen-1] == checkForChar)
	{
		endsWithChar = 1;
	}
	return(endsWithChar);
}

int compareStrings(const char* str1, const char* str2) 
{
	// string1 < string2 => return a negative integer
	// string1 > string2 => return a positive integer
	// string1 = string2 => return 0
    while(*str1 && (*str1 == *str2)) 
    {
        str1++;
        str2++;
    }
    return(*str1 - *str2);
}