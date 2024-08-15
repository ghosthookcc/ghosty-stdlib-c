#include "../../Header Files/stdlib/linkedList.h"

node initLinkedListNode(void* inData)
{
    node newNode = (node)malloc(sizeof(*newNode) + sizeof(inData));
    newNode->value = inData;
    newNode->next = NULL;
    newNode->previous = NULL;
    return newNode;
}

linkedList initLinkedList()
{
    linkedList newLinkedList;
    newLinkedList.size = 0;
    newLinkedList.latestNode = NULL;
    newLinkedList.head = NULL;
    newLinkedList.tail = NULL;
    return newLinkedList;
}

void insertIntoLinkedListBeginning(linkedList* targetPtr, node newNode)
{
    newNode->next = targetPtr->head;
    if (targetPtr->head != NULL)
    {
        targetPtr->head->previous = newNode;
    }
    targetPtr->head = newNode;
    targetPtr->size += 1;
    targetPtr->latestNode = newNode;
    findAndSetTailOfLinkedListUsingNode(targetPtr, targetPtr->latestNode);
}

void insertIntoLinkedListEnd(linkedList* targetPtr, node newNode)
{

}

void findAndSetTailOfLinkedListUsingNode(linkedList* targetPtr, node startNode)
{
    node currentNodeTraversing = startNode;
    while (currentNodeTraversing->next != NULL)
    {
        currentNodeTraversing = currentNodeTraversing->next;
    }
    targetPtr->tail = currentNodeTraversing;
}
