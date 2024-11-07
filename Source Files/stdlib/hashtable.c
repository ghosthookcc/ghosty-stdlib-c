#include "../../Header Files/stdlib/hashtable.h"

openHashTable initOpenHashTable(equalCallback equal, 
                                size_t keySize, size_t valueSize,
                                size_t sizeInMb, size_t alignment)
{
    openHashTable newHashTable = malloc(sizeof(*newHashTable));

    newHashTable->hashSize = sizeof(unsigned int);
    newHashTable->keySize = keySize + newHashTable->hashSize;
    newHashTable->valueSize = valueSize;

    size_t hashtableKeyPairInitSize = sizeInMb * BYTESINMB;

    unsigned int keyArenaCapacity = 0;
    unsigned int valueArenaCapacity = 0;

    size_t keyArenaSize = 0;
    size_t valueArenaSize = 0; 

    size_t totalSize = 0;

    while (true)
    {
        keyArenaCapacity += 1;
        keyArenaSize += newHashTable->keySize;
        totalSize += newHashTable->keySize;

        if (totalSize + valueSize > hashtableKeyPairInitSize) break;

        valueArenaCapacity += 1;
        valueArenaSize += newHashTable->valueSize;
        totalSize += newHashTable->valueSize;
    }

    while (keyArenaSize % alignment != 0)
    {
        keyArenaSize += 1;
    }
    while (valueArenaSize % alignment != 0)
    {
        valueArenaSize += 1;
    }

    hashtableKeyPairInitSize = totalSize;

    newHashTable->capacity = keyArenaCapacity; //- 1;
    newHashTable->entryCount = 0;

    newHashTable->equal = equal;

    newHashTable->keys = initArena(keyArenaSize, alignment);
    newHashTable->values = initArena(valueArenaSize, alignment);

    return newHashTable;
}

void* insertIntoOpenHashTable(openHashTable targetPtr, 
                              void* key, void* value)
{
    if (targetPtr->entryCount == targetPtr->capacity) return NULL;

    boolean foundOpenSlot = false;

    unsigned int hash = fnv1AHash(key, targetPtr->hashSize, 0);
    unsigned int hashTableIdx = hash % targetPtr->capacity;

    unsigned int originalIdx = hashTableIdx;

    entryKey currentEntry;
    currentEntry.key = malloc(targetPtr->keySize); 

    unsigned char* allData = malloc(sizeof(entryKey) + targetPtr->keySize);
    unsigned char* tempAllData = NULL;

    while (hashTableIdx < targetPtr->capacity)
    {
        tempAllData = allData;

        getArenaAtIndex(targetPtr->keys, tempAllData, hashTableIdx, targetPtr->keySize);

        memcpy(&currentEntry.hash, allData, targetPtr->hashSize);
        tempAllData += targetPtr->hashSize;
        memcpy(currentEntry.key, allData, targetPtr->keySize - targetPtr->hashSize);

        if (currentEntry.hash == ARENAENTRYTAKEN) 
        {
            foundOpenSlot = true;
            break;
        }
        if (currentEntry.hash == hash && targetPtr->equal(currentEntry.key, key))
        {
            return key;
        }
        hashTableIdx++;
    }
    if (!foundOpenSlot)
    {
        hashTableIdx = 0;
        while (hashTableIdx < originalIdx)
        {
            tempAllData = allData;

            getArenaAtIndex(targetPtr->keys, tempAllData, hashTableIdx, targetPtr->keySize);

            memcpy(&currentEntry.hash, allData, targetPtr->hashSize);
            tempAllData += targetPtr->hashSize;
            memcpy(currentEntry.key, allData, targetPtr->keySize - targetPtr->hashSize);

            if (currentEntry.hash == ARENAENTRYTAKEN) 
            {
                foundOpenSlot = true;
                break;
            }
            if (currentEntry.hash == hash && targetPtr->equal(currentEntry.key, key))
            {
                return key;
            }
            hashTableIdx++;
        }
    }

    if (foundOpenSlot)
    {
        currentEntry.hash = hash;
        currentEntry.key = key;

        insertIntoArena(targetPtr->keys, &currentEntry, targetPtr->keySize, hashTableIdx);
        insertIntoArena(targetPtr->values, value, targetPtr->valueSize, hashTableIdx);

        targetPtr->entryCount += 1;

        return key;
    }
    return NULL;
}

keyPair searchOpenHashTable(openHashTable targetPtr, void* key)
{
    unsigned int hash = fnv1AHash(key, targetPtr->hashSize, 0);
    unsigned int hashTableIdx = hash % targetPtr->capacity;

    boolean isEqualHash;
    boolean isEqualKey;

    entryKey currentEntry;
    currentEntry.key = malloc(targetPtr->keySize);

    unsigned char* allData = malloc(sizeof(entryKey) + targetPtr->keySize);
    while (hashTableIdx < targetPtr->capacity)
    {
        getArenaAtIndex(targetPtr->keys, allData, hashTableIdx, targetPtr->keySize);

        memcpy(&currentEntry.hash, allData, targetPtr->hashSize);
        allData += targetPtr->hashSize; 
        memcpy(&currentEntry.key, allData, targetPtr->keySize - targetPtr->hashSize);
        
        if (currentEntry.hash != ARENAENTRYTAKEN)
        {
            isEqualHash = currentEntry.hash == hash;
            isEqualKey = targetPtr->equal(currentEntry.key, key);
        
            if (isEqualHash && isEqualKey)
            {
                unsigned char* value = malloc(targetPtr->valueSize);
                getArenaAtIndex(targetPtr->values, value, hashTableIdx, targetPtr->valueSize);
                return initKeyPair(currentEntry.key, value); 
            }
        }
        hashTableIdx++;
        allData -= targetPtr->hashSize;
    }
    return NULL;
}

void freeOpenHashTable(openHashTable targetPtr)
{
    freeArena(targetPtr->keys);
}

keyPair initKeyPair(void* key, void* value)
{
    keyPair newKeyPair = malloc(sizeof(*newKeyPair));

    newKeyPair->key = key;
    newKeyPair->value = value;

    return newKeyPair;
}

boolean unsignedIntEqual(void* data, void* otherData)
{
    const unsigned int data_t = *(unsigned int*)data;
    const unsigned int otherData_t = *(unsigned int*)otherData;

    boolean isEqual = (data_t == otherData_t);
    return isEqual;
}
