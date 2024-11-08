#include "../../Header Files/stdlib/string.h"

/* Start string definition */
string initString()
{
	string newString = malloc(sizeof(*newString) + (sizeof(char) * DEFAULT_STRING_CAPACITY + 1));
	
	newString->chars = malloc((sizeof(char) * DEFAULT_STRING_CAPACITY) + 1);
	newString->realSize = 0;
	newString->capacity = DEFAULT_STRING_CAPACITY;

    gsmemset(newString->chars, DEFAULT_STRING_CAPACITY, '\0');
	newString->chars[DEFAULT_STRING_CAPACITY] = '\0';

	return(newString);
}		

void pushChar(string* target, char item)
{
    string targetDerefed = *target;
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

void pushChars(string* target, char* item)
{
	unsigned int itemCharsLen = sizeof(char) * charsLength(item);
	string targetDerefed = *target;
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

void copyChars(string* target, const unsigned char* source, size_t length)
{
    size_t skipAmountChars = 0;
    while (*source == '\0' && skipAmountChars < length)
    { 
        skipAmountChars += 1;
        *source++;
    }

    length -= skipAmountChars;

    char* tmpData = malloc((sizeof(char) * length) + 1); 
    memcpy(tmpData, source, length);
    tmpData[length] = '\0'; 

    pushChars(target, tmpData);
    free(tmpData);
}

void printString(string target)
{
	printf("\n");
	printf("%s ", target->chars);
	printf("\n");
}

void freeString(string* target)
{
    string targetDerefed = *target;
	free(targetDerefed->chars);
	free(targetDerefed);
}
/* End string definition */

/* Start stringArray definition */
stringArray initStringArray()
{
	stringArray newStringArray = malloc(sizeof(*newStringArray));

    newStringArray->items = malloc(sizeof(newStringArray->items) * DEFAULT_STRING_ARRAY_CAPACITY);
	newStringArray->realSize = 0;
	newStringArray->capacity = DEFAULT_STRING_ARRAY_CAPACITY;

	return(newStringArray);
}

void pushString(stringArray* target, string item)
{
	stringArray targetDerefed = *target;
	if ( targetDerefed->realSize == targetDerefed->capacity )
	{
		// Grow target array by 2k+1
		targetDerefed->capacity = targetDerefed->capacity * 2 + 1;
		targetDerefed->items = realloc(targetDerefed->items, sizeof(string) * targetDerefed->capacity);	
	}
	targetDerefed->items[targetDerefed->realSize] = item;
	targetDerefed->realSize++;
}

void printStringArray(stringArray* target)
{
	printf("\n");
	stringArray targetDerefed = *target;
	for (unsigned int idx = 0; idx < targetDerefed->realSize; idx++)
	{
		printString(targetDerefed->items[idx]);
	}
	printf("\n");
}

void freeStringArray(stringArray* target)
{
	stringArray targetDerefed = *target;
	for (unsigned int idx = 0; idx < targetDerefed->realSize; idx++)
	{
		freeString(&targetDerefed->items[idx]);
	}
	free(targetDerefed->items);
	free(targetDerefed);
}
/* End stringArray definition */

unsigned int charsLength(const char* chars)
{
    const char* offset = chars;
	unsigned int len = 0;
	while (*offset != '\0')
	{
		offset++;
		len++;
	}
	return(len);    
}

unsigned int stringLength(string stringToFindLength)
{
	return charsLength(stringToFindLength->chars);
}

boolean stringEndsWith(string searchString, const char checkForChar)
{
	boolean endsWithChar = false;
	unsigned int searchStringLen = stringLength(searchString);
	if (searchString->chars[searchStringLen-1] == checkForChar)
	{
		endsWithChar = true;
	}
	return(endsWithChar);
}

int compareStrings(string str1, string str2) 
{
	// string1 < string2 => return a negative integer
	// string1 > string2 => return a positive integer
	// string1 = string2 => return 0
    const char* str1Offset = str1->chars;
    const char* str2Offset = str2->chars;
    while(*str1Offset && (*str1Offset == *str2Offset)) 
    {
        str1Offset++;
        str2Offset++;
    }
    return(*str1Offset - *str2Offset);
}

boolean isDigit(const char character)
{
    boolean digit = false;
    if (character >= '0' && character <= '9')
    {
        digit = true;
    }
    return digit;
}

boolean isAlpha(const char character)
{
    boolean alpha = false;
    if (character >= 'a' && character <= 'z'
    ||  character >= 'A' && character <= 'Z')
    {
        alpha = true;
    }
    return alpha;
}

boolean isAlphaDigit(const char character)
{
    boolean alphaDigit = false;
    if (isAlpha(character) || isDigit(character))
    {
        alphaDigit = true;
    }
    return alphaDigit;
}

void stripStringTerminators(const char* charsToSearch, size_t length)
{
    unsigned char* offset = (unsigned char*)charsToSearch;
    for (size_t idx = 0; idx < length; idx++)
    {
        if (idx != length-1 && *offset++ == '\0')
        {
            *offset = ' ';
        }
    }
}
