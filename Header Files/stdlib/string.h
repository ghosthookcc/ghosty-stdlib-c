#ifndef STRING_H
#define STRING_H

#define DEFAULT_STRING_CAPACITY 8
#define DEFAULT_STRING_ARRAY_CAPACITY 8

#include <stdlib.h>
#include <stdio.h>

#include "memory.h"
#include "boolean.h"

/* Start string declaration */
typedef struct string_t
{
	unsigned int realSize;
	unsigned int capacity;
	char* chars;
} *string;

string initString();

void pushChar(string* target, char item);

void pushChars(string* target, char* item);

void copyChars(string* target, const unsigned char* source, size_t length);

void printString(string target);

void freeString(string* target);
/* End string declaration */

/* Start stringArray declaration */
typedef struct stringArray_t
{
	unsigned int realSize;
	unsigned int capacity;
	string* items;
} *stringArray;

stringArray initStringArray();

void pushString(stringArray* target, string item);
void printStringArray(stringArray* target);
void freeStringArray(stringArray* target);
/* End stringArray declaration */

unsigned int charsLength(const char* chars);
unsigned int stringLength(string stringToFindLength);

boolean stringEndsWith(string searchString, const char checkForChar);
int compareStrings(string str1, string str2);

boolean isDigit(const char character);
boolean isAlpha(const char character);
boolean isAlphaDigit(const char character);

void stripStringTerminators(const char* charsToSearch, size_t length);

#endif // STRING_H
