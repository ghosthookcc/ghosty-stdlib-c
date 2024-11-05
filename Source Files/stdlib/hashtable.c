#include "../../Header Files/stdlib/hashtable.h"

openHashTable initOpenHashTable(equalCallback equal, size_t keySize, size_t valueSize)
{
    // 10mb
    size_t hashtableKeyPairInitSize = 10240000;
                                      
    unsigned int keyArenaCapacity = 0;
    unsigned int valueArenaCapacity = 0;

    size_t keyArenaSize = 0;
    size_t valueArenaSize = 0; 

    size_t totalSize = 0;

    while (true)
    {
        keyArenaCapacity += 1;
        keyArenaSize += keySize;
        totalSize += keySize;

        if (totalSize + valueSize > hashtableKeyPairInitSize) break;

        valueArenaCapacity += 1;
        valueArenaSize += valueSize;
        totalSize += valueSize;
    }

    if (keyArenaCapacity > valueArenaCapacity)
    {
        keyArenaCapacity -= 1;
        keyArenaSize -= keySize;
        totalSize -= keySize;
    }

    while (totalSize % 1024 != 0 || totalSize == hashtableKeyPairInitSize)
    {
        totalSize += 1;
    }

    hashtableKeyPairInitSize = totalSize;

    openHashTable newHashTable;

    newHashTable.capacity = keyArenaCapacity; //- 1;
    newHashTable.entryCount = 0;

    newHashTable.keySize = keySize + sizeof(unsigned int);
    newHashTable.valueSize = valueSize;
    newHashTable.hashSize = sizeof(unsigned int);

    newHashTable.equal = equal;

    // 10mb - padding allocated for the arena
    newHashTable.keys = initArena(hashtableKeyPairInitSize);
    // use 10mb - padding - valueArenaSize of the keysArena to split the arena into 2 arenas
    newHashTable.values = initArenaFromArena(&newHashTable.keys, valueArenaSize);

    return newHashTable;
}

void* insertIntoOpenHashTable(openHashTable* targetPtr, 
                              void* key, void* value)
{
    openHashTable dtarget = *targetPtr;

    unsigned int hash = fnv1AHash(key, dtarget.hashSize, 0);
    unsigned int hashTableIdx = hash % dtarget.capacity;

    unsigned int originalIdx = hashTableIdx;

    entryKey currentEntry;
    while (hashTableIdx < dtarget.capacity)
    {        
        getArenaAtIndex(dtarget.keys, &currentEntry, hashTableIdx, dtarget.keySize);
        if (currentEntry.hash == ~((unsigned int)0)) break;
        if (currentEntry.hash == hash && dtarget.equal(currentEntry.key, key))
        {
            return currentEntry.key;
        }
        hashTableIdx++;
    } 

    currentEntry.hash = hash;
    currentEntry.key = key;

    printf("Before :: %d ;", currentEntry.hash);

    insertIntoArena(dtarget.keys, &currentEntry, dtarget.keySize);
    //insertIntoArena(dtarget.values, value, dtarget.valueSize);
    return key;
}

keyPair searchOpenHashTable(openHashTable* targetPtr, void* key)
{
    unsigned int hash = fnv1AHash(key, targetPtr->hashSize, 0);
    unsigned int hashTableIdx = hash % targetPtr->capacity;

    boolean isEqualHash;
    boolean isEqualKey;

    entryKey currentEntry;
    while (hashTableIdx < targetPtr->capacity)
    {
        getArenaAtIndex(targetPtr->keys, &currentEntry, hashTableIdx, targetPtr->keySize);
        printf("\n%d\n", currentEntry.hash);
        if (currentEntry.hash != ~((unsigned int)0))
        {
            printf("After :: %d ;", currentEntry.hash);
            isEqualHash = currentEntry.hash == hash;
            isEqualKey = targetPtr->equal(currentEntry.key, key);
        
            if (isEqualHash && isEqualKey)
            {
                void* valueByKey;
                getArenaAtIndex(targetPtr->values, valueByKey, hashTableIdx, targetPtr->valueSize);
                return initKeyPair(currentEntry.key, valueByKey, targetPtr->keySize, targetPtr->valueSize);
            }
        }
        hashTableIdx++;
    }
    return NULL;
}

void freeOpenHashTable(openHashTable* targetPtr)
{
    openHashTable dtarget = *targetPtr;
    freeArena(&dtarget.keys);
}

keyPair initKeyPair(void* key, void* value, size_t keySize, size_t valueSize)
{
    keyPair newKeyPair = malloc(sizeof(*newKeyPair) + keySize + valueSize);

    newKeyPair->key = malloc(keySize);
    newKeyPair->value = malloc(valueSize);

    memcpy(newKeyPair->key, key, keySize);
    memcpy(newKeyPair->value, value, valueSize);

    return newKeyPair;
}

boolean unsignedIntEqual(void* data, void* otherData)
{
    const unsigned int data_t = *(unsigned int*)data;
    const unsigned int otherData_t = *(unsigned int*)otherData;

    boolean isEqual = (data_t == otherData_t);
    return isEqual;
}