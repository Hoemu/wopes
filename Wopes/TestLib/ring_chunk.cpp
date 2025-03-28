#include "ring_chunk.h"
#include <iostream>

RingChunk::RingChunk(const size_t &ringBufferSize)
{
    readIndex.store(0);
    writeIndex.store(0);

    chunkNumber = ringBufferSize;
    for (int i = 0; i < ringBufferSize; i++)
    {
        chunkArray.push_back(make_unique<CharChunk>(nearestPowerOfTwo(ringBufferSize)));
    }

    lenMask = chunkNumber;
    mask = lenMask;
    storeSize = chunkNumber * chunkArray.size();
}

void RingChunk::push(char *var) noexcept
{
    // std::unique_lock<std::mutex> lock(mutex_);
    // cvPush.wait(lock, [this] { return !full(); });

    int strBegin = 0;
    int strEnd = strlen(var);

    while (writeIndex < strEnd && strBegin < strEnd)
    {
        strBegin = chunkArray[writeIndex & mask]->copyMemory(var, strBegin, strEnd);
        writeIndex.fetch_add(1, std::memory_order_release);
    }

    // 如果当前内存块满了，新申请一个内存块 [2]
    // cvPop.notify_one();
}

CharChunk *RingChunk::pop()
{
    // std::unique_lock<std::mutex> lock(mutex_);
    // cvPop.wait(lock, [this] { return !empty(); });

    readIndex.fetch_add(1, std::memory_order_acquire);
    CharChunk *item = chunkArray[readIndex & mask].get();

    // cvPush.notify_one();
    return item;
}

unsigned int RingChunk::getStoreSize() const
{
    return storeSize;
}

inline size_t RingChunk::size() const
{
    return writeIndex.load(std::memory_order_acquire) - readIndex.load(std::memory_order_acquire);
}

bool RingChunk::full() const
{
    return size() >= chunkNumber;
}

bool RingChunk::empty() const
{
    return readIndex == writeIndex;
}

inline size_t RingChunk::nearestPowerOfTwo(size_t n) const
{
    if (n & (n - 1))
    {
        n |= n >> 1;
        n |= n >> 2;
        n |= n >> 4;
        n |= n >> 8;
        n |= n >> 16;
        return n + 1;
    }
    return n;
}
