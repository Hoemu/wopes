#include "char_chunk.h"
#include <iostream>

CharChunk::CharChunk(size_t len)
{
    memorySize = len;
    remainingMemory = len;
    readPtr = 0;
    memoryChunk = (char *)malloc(len + 1);

    if (!memoryChunk)
    {
        throw std::bad_alloc(); // 或通过其他方式处理异常
    }
}

CharChunk::~CharChunk()
{
    if (memoryChunk)
    {
        free(memoryChunk);
        memoryChunk = nullptr; // 防止重复释放
    }
}

CharChunk::CharChunk(const CharChunk &other)
{
    memorySize = other.memorySize;
    remainingMemory = other.remainingMemory;
    readPtr = other.readPtr;
    memoryChunk = (char *)malloc(memorySize + 1);
    memcpy(memoryChunk, other.memoryChunk, memorySize + 1);
}

int CharChunk::copyMemory(const char *var, const int &chBeign, const int &chEnd)
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
    }
    remainingMemory = memorySize - readPtr;
    memoryChunk[readPtr] = '\0';

    return varRecorder;
}

char *CharChunk::getMemroyChunk() const
{
    return memoryChunk;
}

inline bool CharChunk::isFull() const
{
    return memorySize == readPtr ? true : false;
}

size_t CharChunk::size() const
{
    return memorySize;
}

void CharChunk::resetMemory()
{
    readPtr = 0;
    remainingMemory = memorySize;
    std::cout << "[is full:" << isFull() << "]";
}
