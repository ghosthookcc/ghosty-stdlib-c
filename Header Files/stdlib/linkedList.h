#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node_t
{
    struct node_t* next;
    struct node_t* previous;
    void* value;
} *node;

typedef struct linkedList_t
{
    int size;
    node latestNode;
    node head;
    node tail;
} *linkedList;

linkedList initLinkedList();
node insertIntoLinkedListBeginning(linkedList* targetPtr,  node inData);
void insertIntoLinkedListEnd(linkedList* targetPtr, node inData);

void findAndSetTailOfLinkedListUsingNode(linkedList* targetPtr, node startNode);

void freeLinkedList(linkedList* targetPtr);

node initLinkedListNode(void* inData);

#endif // LINKEDLIST_H
