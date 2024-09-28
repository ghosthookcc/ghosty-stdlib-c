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

openHashTable initOpenHashTable(unsigned int capacity, double loadFactor)
{
    openHashTable newHashTable = (openHashTable)malloc(sizeof(*newHashTable) + sizeof(openHashTableBucket) * capacity);
    newHashTable->buckets = (openHashTableBucket*)malloc(sizeof(openHashTableBucket) * capacity);
    for (unsigned int idx = 0; idx < capacity; idx++)
    {
        newHashTable->buckets[idx] = NULL;
    }
    newHashTable->entryCount = 0;
    newHashTable->capacity = capacity;
    newHashTable->loadFactor = loadFactor;
    return newHashTable;
}

keyPair insertIntoOpenHashTable(openHashTable* targetPtr, void* key, void* value, unsigned int keyLength, equalCallback equal)
{
    openHashTable dtarget = *targetPtr;
 
    double currentLoadFactor = (double)((1.0 * dtarget->entryCount) / dtarget->capacity);
    if (currentLoadFactor > dtarget->loadFactor)
    {
        expandOpenHashTable(targetPtr);
    }

    unsigned int hash = fnv1AHash(key, keyLength, 0);
    unsigned int hashTableIdx = hash % dtarget->capacity;

    keyPair newKeyPair = initKeyPair(key, value, keyLength, equal);
    openHashTableBucket openBucket = dtarget->buckets[hashTableIdx];

    unsigned int bucketCreateIdx;
    boolean createBucket = false;
    if (openBucket == NULL)
    {
        openBucket = dtarget->buckets[hashTableIdx];
        bucketCreateIdx = hashTableIdx;
        createBucket = true;
    }
    else if (openBucket->_bucket.hash == hash && openBucket->data->equal(openBucket->data->key, key))
    {
        openBucket->data->value = newKeyPair->value;
        free(newKeyPair);
        return openBucket->data;
    }
    else
    {
        unsigned int hashTableIdxAlternate = hashTableIdx+1;
        while (hashTableIdxAlternate < dtarget->capacity)
        {            
            openBucket = dtarget->buckets[hashTableIdxAlternate];
            if (openBucket == NULL)
            {
                bucketCreateIdx = hashTableIdxAlternate;
                createBucket = true;
                break;
            }
            hashTableIdxAlternate++;
        }
    }

    if (createBucket) 
    {
        dtarget->buckets[bucketCreateIdx] = initOpenHashTableBucket(hash, newKeyPair);
        dtarget->buckets[bucketCreateIdx]->_bucket.size += 1;
        dtarget->entryCount += 1;

        return dtarget->buckets[bucketCreateIdx]->data;
    }
    return NULL;
}

void insertAndRehashOpenHashTableEntry(openHashTableBucket* bucketsPtr, openHashTableBucket bucketToHash, unsigned int startIdx, unsigned int capacity)
{
    openHashTableBucket openBucket = bucketsPtr[startIdx]; 
    while (openBucket != NULL && startIdx < capacity)
    {
        openBucket = bucketsPtr[startIdx];
        startIdx += 1;
    }
    bucketsPtr[startIdx] = bucketToHash;
}

keyPair searchOpenHashTable(openHashTable targetPtr, void* key, unsigned int keyLength)
{
    unsigned int hash = fnv1AHash(key, keyLength, 0);
    unsigned int hashTableIdx = hash % targetPtr->capacity;

    boolean isEqualHash;
    boolean isEqualKey;

    openHashTableBucket openBucket = NULL;
    while (hashTableIdx < targetPtr->capacity)
    {
        openBucket = targetPtr->buckets[hashTableIdx]; 
        if (openBucket == NULL) 
        {
            hashTableIdx++;
            continue;
        }

        isEqualHash = openBucket->_bucket.hash == hash;
        isEqualKey = openBucket->data->equal(openBucket->data->key, key);
        
        if (isEqualHash && isEqualKey)
        {
            return openBucket->data;
        }
        hashTableIdx++;
    }
    return NULL;
}

void expandOpenHashTable(openHashTable* targetPtr)
{
    openHashTable dtarget = *targetPtr;
    openHashTableBucket* tmpBuckets = (openHashTableBucket*)malloc(sizeof(openHashTableBucket) * dtarget->capacity);

    for (unsigned int idx = 0; idx < dtarget->capacity; idx++)
    {
        tmpBuckets[idx] = dtarget->buckets[idx];
    }

    unsigned int originalCapacity = dtarget->capacity;
    dtarget->capacity = originalCapacity * 2 + 1;
    dtarget->buckets = realloc(dtarget->buckets, sizeof(struct openHashTableBucket_t) * dtarget->capacity);
    for (unsigned int idx = 0; idx < dtarget->capacity; idx++)
    {
        dtarget->buckets[idx] = NULL;
    }

    openHashTableBucket currentBucket = NULL;
    unsigned int newBucketIdx = 0;
    for (unsigned int idx = 0; idx < originalCapacity; idx++)
    {
        currentBucket = tmpBuckets[idx];
        if (currentBucket != NULL)
        {
            newBucketIdx = currentBucket->_bucket.hash % dtarget->capacity;
            insertAndRehashOpenHashTableEntry(dtarget->buckets, currentBucket, newBucketIdx, dtarget->capacity);
        }
    }
    free(tmpBuckets);
}

void freeOpenBuckets(openHashTableBucket* bucketsPtr, unsigned int capacity)
{
    unsigned int idx = 0;
    while (idx < capacity)
    {
        if (bucketsPtr[idx] != NULL)
        {
            openHashTableBucket currentBucket = bucketsPtr[idx];
            free(currentBucket->data);
            free(currentBucket);
        }
        idx += 1;
    }
    free(bucketsPtr);
}
void freeOpenHashTable(openHashTable* targetPtr)
{
    openHashTable dtarget = *targetPtr;
    freeOpenBuckets(dtarget->buckets, dtarget->capacity);
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