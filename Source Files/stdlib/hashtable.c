#include "../../Header Files/stdlib/hashTable.h"

hashTable initHashTable(equalCallback equal, 
                                size_t keySize, size_t valueSize,
                                size_t sizeInMb, size_t alignment)
{
    hashTable newHashTable = malloc(sizeof(*newHashTable));

    newHashTable->hashSize = sizeof(unsigned int);
    newHashTable->keySize = keySize;
    newHashTable->valueSize = valueSize;
    newHashTable->keyEntrySize = newHashTable->keySize + newHashTable->hashSize;

    size_t hashTableKeyPairInitSize = sizeInMb * BYTESINMB;

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

        if (totalSize + valueSize > hashTableKeyPairInitSize) break;

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

    hashTableKeyPairInitSize = totalSize;

    newHashTable->capacity = keyArenaCapacity; //- 1;
    newHashTable->entryCount = 0;

    newHashTable->equal = equal;

    newHashTable->keys = initArena(keyArenaSize, alignment);
    newHashTable->values = initArena(valueArenaSize, alignment);

    return newHashTable;
}

void* insertIntoHashTable(hashTable targetPtr, 
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
            free(foundKey);
            break;
        }
        
        memcpy(foundKey, dataPtr+targetPtr->hashSize, targetPtr->keySize);
        if (foundHash == hash && targetPtr->equal(foundKey, key))
        {
            memcpy((unsigned char*)targetPtr->values->storage+(hashTableIdx * targetPtr->valueSize), value, 0);
            free(foundKey);
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
                free(foundKey);
                break;
            }

            memcpy(foundKey, dataPtr+targetPtr->hashSize, targetPtr->keySize);
            if (foundHash == hash && targetPtr->equal(foundKey, key))
            {
                free(foundKey);
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
    free(foundKey);
    return NULL;
}

keyPair searchHashTable(hashTable targetPtr, void* key)
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
                keyPair kvp = initKeyPair(foundKey, value,
                                          targetPtr->keySize, targetPtr->valueSize);
                free(foundKey);
                return kvp;
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
                keyPair kvp = initKeyPair(foundKey, value,
                                          targetPtr->keySize, targetPtr->valueSize);
                free(foundKey);
                return kvp;
            }
        }
    } 
    return NULL;
}

void freeHashTable(hashTable targetPtr)
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

boolean charsEqual(void* data, void* otherData)
{
    const char* data_t = *(char*)data;
    const char* otherData_t = *(char*)otherData;

    string dataStr = initString();
    string otherDataStr = initString();

    pushChars(&dataStr, data_t);
    pushChars(&otherDataStr, otherData_t);

    boolean isEqual = (compareStrings(dataStr, otherDataStr) == 0);
    freeString(&dataStr);
    freeString(&otherDataStr);
    return isEqual;
}

boolean stringEqual(void* data, void* otherData)
{
    const string data_t = *(string*)data;
    const string otherData_t = *(string*)otherData;

    boolean isEqual = (compareStrings(data_t, otherData_t) == 0);
    return isEqual;
}
