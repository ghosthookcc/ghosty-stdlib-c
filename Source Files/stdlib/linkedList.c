#include "../../Header Files/stdlib/linkedList.h"

node initLinkedListNode(void* inData)
{
    node newNode = (node)malloc(sizeof(*newNode));
    newNode->next = NULL;
    newNode->previous = NULL;
    newNode->value = inData;
    return newNode;
}

linkedList initLinkedList()
{
    linkedList newLinkedList = (linkedList)malloc(sizeof(*newLinkedList));
    newLinkedList->size = 0;
    newLinkedList->latestNode = NULL;
    newLinkedList->head = NULL;
    newLinkedList->tail = NULL;
    return newLinkedList;
}

void insertIntoLinkedListBeginning(linkedList* targetPtr, node newNode)
{
    linkedList dtarget = *targetPtr;
    newNode->next = dtarget->head;
    if (dtarget->head != NULL)
    {
        dtarget->head->previous = newNode;
    }
    dtarget->head = newNode;
    dtarget->size += 1;
    dtarget->latestNode = newNode;
    findAndSetTailOfLinkedListUsingNode(targetPtr, dtarget->latestNode);
}

void insertIntoLinkedListEnd(linkedList* targetPtr, node newNode)
{

}

void findAndSetTailOfLinkedListUsingNode(linkedList* targetPtr, node startNode)
{
    linkedList dtarget = *targetPtr;
    node currentNodeTraversing = startNode;
    while (currentNodeTraversing->next != NULL)
    {
        currentNodeTraversing = currentNodeTraversing->next;
    }
    dtarget->tail = currentNodeTraversing;
}
