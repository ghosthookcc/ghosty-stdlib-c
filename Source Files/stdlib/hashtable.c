#include "../../Header Files/stdlib/hashtable.h"

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

keyPair insertIntoChainedHashTable(chainedHashTable* targetPtr, void* key, void* value, unsigned int keyLength, equalCallback equal)
{
    chainedHashTable dtarget = *targetPtr;
    unsigned int hash = fnv1AHash(key, keyLength, 0);
    unsigned int hashTableIdx = hash % dtarget->capacity;

    keyPair keyPairToInsert = initKeyPair(key, value, keyLength, equal);

    if (dtarget->chains[hashTableIdx] == NULL)
    {
        dtarget->chains[hashTableIdx] = initLinkedList();
    }

    linkedList entry = dtarget->chains[hashTableIdx];
    node newEntryNode = NULL;
    if (entry->head == NULL)
    {
        chainedHashTableBucket newBucket = initChainedHashTableBucket(hash, keyPairToInsert);
        newBucket->_bucket.size = 1;
        newEntryNode = initLinkedListNode(newBucket);
    }
    else
    {
        node currentNode = entry->head;
        chainedHashTableBucket currentBucket = NULL;
        keyPair currentKeyPair = NULL;
        while (currentNode != NULL)
        {
            currentBucket = ((chainedHashTableBucket)currentNode->value);
            currentKeyPair = ((keyPair)currentBucket->data);
            if (currentBucket == NULL)
            {
                chainedHashTableBucket newBucket = initChainedHashTableBucket(hash, keyPairToInsert);
                newEntryNode = initLinkedListNode(&newBucket);
                currentNode->value = newEntryNode;
                newBucket->_bucket.size += 1;
                currentBucket = newBucket;
            }
            else if (currentBucket->_bucket.hash == hash && currentKeyPair->equal(currentKeyPair->key, keyPairToInsert->key))
            {
                ((keyPair)currentBucket->data)->value = keyPairToInsert->value;
                free(keyPairToInsert);
                return currentBucket->data;
            }
            currentNode = currentNode->next;
        }
    }

    if (newEntryNode != NULL)
    {
        insertIntoLinkedListBeginning(&entry, newEntryNode);
        dtarget->entryCount += 1;
        return keyPairToInsert;
    }
    return NULL;
}

keyPair searchChainedHashTable(chainedHashTable targetPtr, keyPair searchForKeyPair)
{
    unsigned int hash = fnv1AHash(searchForKeyPair->key, searchForKeyPair->keyLength, 0);
    unsigned int hashTableIdx = hash % targetPtr->capacity;

    linkedList entry = targetPtr->chains[hashTableIdx];

    node currentNode = entry->head;
    chainedHashTableBucket currentBucket = NULL;
    keyPair currentKeyPair = NULL;
    while (currentNode != NULL)
    {
        currentBucket = ((chainedHashTableBucket)currentNode->value);
        currentKeyPair = ((keyPair)currentBucket->data);
        if (currentBucket != NULL && currentBucket->_bucket.hash == hash && currentKeyPair->equal(currentKeyPair->key, searchForKeyPair->key))
        {
            return currentKeyPair;
        }
        currentNode = currentNode->next;
    }
    return NULL;
}

chainedHashTableBucket initChainedHashTableBucket(unsigned int hash, void* data)
{
    chainedHashTableBucket newHashTableBucket = (chainedHashTableBucket)malloc(sizeof(*newHashTableBucket));
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
            chainedHashTableBucket currentBucket = NULL;
            node currentNode = dtarget->chains[idx]->head;
            while (currentNode != NULL)
            {
                currentBucket = (chainedHashTableBucket)dtarget->chains[idx]->head->value;
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

openHashTable initOpenHashTable(unsigned int capacity)
{
    openHashTable newHashTable = (openHashTable)malloc(sizeof(*newHashTable) + sizeof(openHashTableBucket) * capacity);
    newHashTable->buckets = (openHashTableBucket*)malloc(sizeof(openHashTableBucket) * capacity);
    newHashTable->entryCount = 0;
    newHashTable->capacity = capacity;
    for (unsigned int idx = 0; idx < capacity; idx++)
    {
        newHashTable->buckets[idx] = NULL;
    }
    return newHashTable;
}

keyPair insertIntoOpenHashTable(openHashTable* targetPtr, void* key, void* value, unsigned int keyLength, equalCallback equal)
{
    openHashTable dtarget = *targetPtr;
    unsigned int hash = fnv1AHash(key, keyLength, 0);
    unsigned int hashTableIdx = hash % dtarget->capacity;

    keyPair newKeyPair = initKeyPair(key, value, keyLength, equal);

    openHashTableBucket openBucket = dtarget->buckets[hashTableIdx];
    if (openBucket == NULL)
    {
        dtarget->buckets[hashTableIdx] = initOpenHashTableBucket(hash, newKeyPair);
        dtarget->buckets[hashTableIdx]->_bucket.size += 1;
        return dtarget->buckets[hashTableIdx]->data;
    }

    if (openBucket->_bucket.hash == hash && openBucket->data->equal(openBucket->data->key, newKeyPair->key))
    {
        openBucket->data->value = newKeyPair->value;
        free(newKeyPair);
        return openBucket->data;
    }

    unsigned int hashTableIdxAlternate = hashTableIdx + 1;
    while (hashTableIdxAlternate < dtarget->capacity)
    {
        openBucket = dtarget->buckets[hashTableIdxAlternate];
        if (openBucket != NULL && openBucket->_bucket.hash == hash && openBucket->data->equal(key, newKeyPair->key))
        {
            openBucket = initOpenHashTableBucket(hash, newKeyPair);
            openBucket->_bucket.size += 1;
            return openBucket->data;
        }
        hashTableIdxAlternate++;
    }
    return NULL;
}

keyPair searchOpenHashTable(openHashTable targetPtr, keyPair searchForKeyPair)
{
    unsigned int hash = fnv1AHash(searchForKeyPair->key, searchForKeyPair->keyLength, 0);
    unsigned int hashTableIdx = hash % targetPtr->capacity;

    openHashTableBucket openBucket = NULL;
    while (hashTableIdx < targetPtr->capacity)
    {
        openBucket = targetPtr->buckets[hashTableIdx]; 
        if (openBucket != NULL && openBucket->_bucket.hash == hash && openBucket->data->equal(openBucket->data->key, searchForKeyPair->key))
        {
            return openBucket->data;
        }
        hashTableIdx++;
    }
    return NULL;
}

void freeOpenHashTable(openHashTable* targetPtr)
{
    openHashTable dtarget = *targetPtr;
    unsigned int idx = 0;
    while (idx < dtarget->capacity)
    {
        if (dtarget->buckets[idx] != NULL)
        {
            openHashTableBucket currentBucket = dtarget->buckets[idx];
            free(currentBucket->data);
            free(currentBucket);
        }
        idx += 1;
    }
    free(dtarget->buckets);
    free(dtarget);
}

openHashTableBucket initOpenHashTableBucket(unsigned int hash, keyPair data)
{
    openHashTableBucket newHashTableBucket = (openHashTableBucket)malloc(sizeof(*newHashTableBucket));
    newHashTableBucket->_bucket = initHashBucket(hash);
    newHashTableBucket->data = data;
    return newHashTableBucket;
}

keyPair initKeyPair(void* key, void* value, unsigned int keyLength, equalCallback equal)
{
    keyPair newKeyPair = (keyPair)malloc(sizeof(*newKeyPair));
    newKeyPair->key = key;
    newKeyPair->value = value;
    newKeyPair->keyLength = keyLength;
    newKeyPair->equal = equal;
    return newKeyPair;
}

boolean unsignedIntEqual(void* data, void* otherData)
{
    const unsigned int data_t = *(unsigned int*)data;
    const unsigned int otherData_t = *(unsigned int*)otherData;

    boolean isEqual = (data_t == otherData_t);
    return isEqual;
}