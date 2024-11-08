#include "../../Header Files/stdlib/hashtable.h"

HashTable initHashTable(equalCallback equal, 
                                size_t keySize, size_t valueSize,
                                size_t sizeInMb, size_t alignment)
{
    HashTable newHashTable = malloc(sizeof(*newHashTable));

    newHashTable->hashSize = sizeof(unsigned int);
    newHashTable->keySize = keySize;
    newHashTable->valueSize = valueSize;
    newHashTable->keyEntrySize = newHashTable->keySize + newHashTable->hashSize;

    size_t hashtableKeyPairInitSize = sizeInMb * BYTESINMB;

    unsigned int keyArenaCapacity = 0;
    unsigned int valueArenaCapacity = 0;

    size_t keyArenaSize = 0;
    size_t valueArenaSize = 0; 

    size_t totalSize = 0;

    while (true)
    {
        keyArenaCapacity += 1;
        keyArenaSize += newHashTable->keyEntrySize;
        totalSize += newHashTable->keyEntrySize;

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

void* insertIntoHashTable(HashTable targetPtr, 
                              void* key, void* value)
{
    if (targetPtr->entryCount == targetPtr->capacity) return NULL;

    boolean foundOpenSlot = false;

    unsigned int hash = fnv1AHash(key, targetPtr->hashSize, 0);
    unsigned int hashTableIdx = hash % targetPtr->capacity;
    unsigned int originalIdx = hashTableIdx;

    unsigned char* dataPtr = NULL;

    unsigned int foundHash = ARENAENTRYTAKEN;
    unsigned char* foundKey = malloc(sizeof(char) * targetPtr->keySize);
    while (hashTableIdx < targetPtr->capacity)
    {
        dataPtr = (unsigned char*)targetPtr->keys->storage+(hashTableIdx * targetPtr->keyEntrySize);

        memcpy(&foundHash, dataPtr, targetPtr->hashSize);
        if (foundHash == ARENAENTRYTAKEN) 
        {
            foundOpenSlot = true;
            break;
        }
        
        memcpy(foundKey, dataPtr+targetPtr->hashSize, targetPtr->keySize);
        if (foundHash == hash && targetPtr->equal(foundKey, key))
        {
            memcpy((unsigned char*)targetPtr->values->storage+(hashTableIdx * targetPtr->valueSize), value, 0);
            return key;
        }
        hashTableIdx++;
    }
    if (!foundOpenSlot)
    {
        hashTableIdx = 0;
        while (hashTableIdx < originalIdx)
        {
            dataPtr = (unsigned char*)targetPtr->keys->storage+(hashTableIdx * targetPtr->keyEntrySize);

            memcpy(&foundHash, dataPtr, targetPtr->hashSize);
            if (foundHash == ARENAENTRYTAKEN) 
            {
                foundOpenSlot = true;
                break;
            }

            memcpy(foundKey, dataPtr+targetPtr->hashSize, targetPtr->keySize);
            if (foundHash == hash && targetPtr->equal(foundKey, key))
            {
                return key;
            }
            hashTableIdx++;
        }
    }

    if (foundOpenSlot)
    {
        insertIntoArena(targetPtr->keys, &hash, targetPtr->hashSize, 0, hashTableIdx);
        insertIntoArena(targetPtr->keys, key, targetPtr->keySize, targetPtr->hashSize, hashTableIdx);

        insertIntoArena(targetPtr->values, value, targetPtr->valueSize, 0, hashTableIdx);

        targetPtr->entryCount += 1;
        return key;
    }
    return NULL;
}

keyPair searchHashTable(HashTable targetPtr, void* key)
{
    unsigned int hash = fnv1AHash(key, targetPtr->hashSize, 0);
    unsigned int hashTableIdx = hash % targetPtr->capacity;
    unsigned int originalIdx = hashTableIdx;

    unsigned char* dataPtr = NULL;

    unsigned int foundHash = ARENAENTRYTAKEN;
    unsigned char* foundKey = malloc(sizeof(char) * targetPtr->keySize);
    while (hashTableIdx < targetPtr->capacity)
    {
        dataPtr = (unsigned char*)targetPtr->keys->storage+(targetPtr->hashSize * hashTableIdx);

        memcpy(&foundHash, dataPtr, targetPtr->hashSize);    
        if (foundHash != ARENAENTRYTAKEN)
        {
            memcpy(foundKey, dataPtr+targetPtr->hashSize, targetPtr->keySize);
            if (foundHash == hash && targetPtr->equal(foundKey, key))
            {
                unsigned char* value = (unsigned char*)targetPtr->values->storage+(targetPtr->valueSize * hashTableIdx); 
                return initKeyPair(foundKey, value,
                                   targetPtr->keySize, targetPtr->valueSize);
            }
        }
        hashTableIdx++;
    }
    while (hashTableIdx < originalIdx)
    {
        dataPtr = (unsigned char*)targetPtr->keys->storage+(targetPtr->hashSize * hashTableIdx);

        memcpy(&foundHash, dataPtr, targetPtr->hashSize);
        if (foundHash != ARENAENTRYTAKEN)
        {
            memcpy(foundKey, dataPtr+targetPtr->hashSize, targetPtr->keySize);
            if (foundHash == hash && targetPtr->equal(foundKey, key))
            {
                unsigned char* value = (unsigned char*)targetPtr->values->storage+(targetPtr->valueSize * hashTableIdx);
                return initKeyPair(foundKey, value,
                                   targetPtr->keySize, targetPtr->valueSize);
            }
        }
    } 
    return NULL;
}

void freeHashTable(HashTable targetPtr)
{
    freeArena(targetPtr->keys);
    freeArena(targetPtr->values);
    free(targetPtr);
}

keyPair initKeyPair(void* key, void* value, 
                    size_t keySize, size_t valueSize)
{
    keyPair newKeyPair = malloc(sizeof(*newKeyPair) + keySize + valueSize);

    newKeyPair->key   = malloc(keySize);
    newKeyPair->value = malloc(valueSize);

    memcpy(newKeyPair->key, key, keySize);
    memcpy(newKeyPair->value, value, valueSize);

    return newKeyPair;
}

void freeKeyPair(keyPair targetPtr)
{
    free(targetPtr->key);
    free(targetPtr->value);
    free(targetPtr);
}

boolean unsignedIntEqual(void* data, void* otherData)
{
    const unsigned int data_t = *(unsigned int*)data;
    const unsigned int otherData_t = *(unsigned int*)otherData;

    boolean isEqual = (data_t == otherData_t);
    return isEqual;
}
