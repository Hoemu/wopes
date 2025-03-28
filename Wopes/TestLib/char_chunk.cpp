#include "char_chunk.h"

CharChunk::CharChunk(const CharChunk &other)
{
    memorySize = other.memorySize;
    remainingMemory = other.remainingMemory;
    readPtr = other.readPtr;
    memoryChunk = (char *)malloc(memorySize + 1);
    memcpy(memoryChunk, other.memoryChunk, memorySize + 1);
}

int CharChunk::copyMemory(char *var, const int &chBeign, const int &chEnd)
{
    if (isFull())
    {
        return readPtr;
    }

    long long len = chEnd - chBeign;
    long long varRecorder = -1;

    if (len < remainingMemory)
    {
        memcpy(memoryChunk + readPtr, var + chBeign, len);
        readPtr = readPtr + len;
        varRecorder = chBeign + len;
    }
    else
    {
        memcpy(memoryChunk + readPtr, var + chBeign, remainingMemory);
        varRecorder = chBeign + remainingMemory;
        readPtr = readPtr + remainingMemory;
        memoryChunk[readPtr] = '\0';
    }
    remainingMemory = memorySize - readPtr;

    return varRecorder;
}

char *CharChunk::getMemroyChunk()
{
    return memoryChunk;
}

inline bool CharChunk::isFull() const
{
    return memorySize == readPtr ? true : false;
}
