#include "../../Header Files/stdlib/hashtable.h"
#include <sys/types.h>

chainedHashTable initChainedHashTable(unsigned int capacity)
{
    chainedHashTable newHashTable = (chainedHashTable)malloc(sizeof(*newHashTable) + sizeof(linkedList) * capacity);
    newHashTable->chains = (linkedList*)malloc(sizeof(linkedList) * capacity);
    for (unsigned int idx = 0; idx < capacity; idx++)
    {
        newHashTable->chains[idx] = NULL;
    }
    newHashTable->entryCount = 0;
    newHashTable->capacity = capacity;
    return newHashTable;
}

void insertIntoChainedHashTable(chainedHashTable* targetPtr, keyPair keyPairToInsert)
{
    chainedHashTable dtarget = *targetPtr;
    unsigned int hash = fnv1AHash(keyPairToInsert->key, keyPairToInsert->keyLength, 0);
    unsigned int hashTableIdx = hash % dtarget->capacity;

    if (dtarget->chains[hashTableIdx] == NULL)
    {
        dtarget->chains[hashTableIdx] = initLinkedList();
    }

    linkedList entry = dtarget->chains[hashTableIdx];
    node newEntryNode = NULL;
    if (entry->head == NULL)
    {
        hashTableBucket newBucket = initHashTableBucket(hash, keyPairToInsert);
        newBucket->_bucket.size = 1;
        newEntryNode = initLinkedListNode(newBucket);
    }
    else
    {
        node currentNode = entry->head;
        hashTableBucket currentBucket = NULL;
        while (currentNode != NULL)
        {
            currentBucket = ((hashTableBucket)currentNode->value);
            if (currentBucket == NULL)
            {
                hashTableBucket newBucket = initHashTableBucket(hash, keyPairToInsert);
                newEntryNode = initLinkedListNode(&newBucket);
                currentNode->value = newEntryNode;
                newBucket->_bucket.size += 1;
                currentBucket = newBucket;
            }
            else if (currentBucket->_bucket.hash == hash)
            {
                free(currentBucket->data);
                currentBucket->data = keyPairToInsert;
            }
            currentNode = currentNode->next;
        }
    }

    if (newEntryNode != NULL)
    {
        insertIntoLinkedListBeginning(&entry, newEntryNode);
        dtarget->entryCount += 1;
    }
}

keyPair searchChainedHashTable(chainedHashTable targetPtr, keyPair keyPair)
{
    unsigned int hash = fnv1AHash(keyPair->key, keyPair->keyLength, 0);
    unsigned int hashTableIdx = hash % targetPtr->capacity;

    linkedList entry = targetPtr->chains[hashTableIdx];

    node currentNode = entry->head;
    hashTableBucket currentBucket = NULL;
    while (currentNode != NULL)
    {
        currentBucket = ((hashTableBucket)currentNode->value);
        if (currentBucket != NULL && currentBucket->_bucket.hash == hash)
        {
            return (currentBucket->data);
        }
        currentNode = currentNode->next;
    }
    return NULL;
}

keyPair initKeyPair(void* key, void* value, unsigned int keyLength)
{
    keyPair newKeyPair = (keyPair)malloc(sizeof(*newKeyPair));
    newKeyPair->key = key;
    newKeyPair->value = value;
    newKeyPair->keyLength = keyLength;
    return newKeyPair;
}

hashTableBucket initHashTableBucket(unsigned int hash, void* data)
{
    hashTableBucket newHashTableBucket = (hashTableBucket)malloc(sizeof(*newHashTableBucket));
    newHashTableBucket->_bucket = initHashBucket(hash);
    newHashTableBucket->data = data;
    return newHashTableBucket;
}

void freeChainedHashTable(chainedHashTable* targetPtr)
{
    chainedHashTable dtarget = *targetPtr;
    unsigned int idx = 0;
    while (idx < dtarget->capacity)
    {
        if (dtarget->chains[idx] != NULL)
        {
            hashTableBucket currentBucket = NULL;
            node currentNode = dtarget->chains[idx]->head;
            while (currentNode != NULL)
            {
                currentBucket = (hashTableBucket)dtarget->chains[idx]->head->value;
                free(currentBucket->data);
                free(currentBucket);
                currentNode = currentNode->next;
            }
            freeLinkedList(&dtarget->chains[idx]);
        }
        idx += 1;
    }
    free(dtarget->chains);
    free(dtarget);
}
