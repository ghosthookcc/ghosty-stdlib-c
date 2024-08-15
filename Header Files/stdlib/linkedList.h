#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node_t
{
    void* value;
    struct node_t* next;
    struct node_t* previous;
} *node;

typedef struct linkedList_t
{
    int size;
    node latestNode;
    node head;
    node tail;
} linkedList;

node initLinkedListNode(void* inData);

linkedList initLinkedList();
void insertIntoLinkedListBeginning(linkedList* targetPtr,  node inData);
void insertIntoLinkedListEnd(linkedList* targetPtr, node inData);

void findAndSetTailOfLinkedListUsingNode(linkedList* targetPtr, node startNode);

#endif // LINKEDLIST_H
