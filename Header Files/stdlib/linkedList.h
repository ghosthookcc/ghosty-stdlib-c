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
    // Why not previous too?
} *node;

typedef struct linkedList_t
{
    int size;
    node head;
    // Why not tail?
} linkedList;

node initLinkedListNode(void* inData);

linkedList initLinkedList();
void insertIntoLinkedListBeginning(linkedList* targetPtr,  node inData);
void insertIntoLinkedListEnd(linkedList* targetPtr, node inData);

#endif // LINKEDLIST_H
