#ifndef STRING_H
#define STRING_H

#include <stdlib.h>
#include <stdio.h>

/* Start string declaration */

typedef struct string
{
	char* chars;
	unsigned int realSize;
	unsigned int capacity;
} string;

string* initString(unsigned int initCapacity);

void pushChar(string** target, char item);

void pushChars(string** target, char* item);

void printString(string** target);

void freeString(string** target);

/* End string declaration */

/* Start stringArray declaration */

typedef struct stringArray
{
	string** items;
	unsigned int realSize;
	unsigned int capacity;
} stringArray;

stringArray* initStringArray(unsigned int initCapacity);

void pushString(stringArray** target, string* item);

void printStringArray(stringArray** target);

void freeStringArray(stringArray** target);

/* End stringArray declaration */

unsigned int getStringLen(char* chars);

unsigned char stringEndsWith(char* string, char checkForChar);

int compareStrings(const char* str1, const char* str2);

#endif // STRING_H