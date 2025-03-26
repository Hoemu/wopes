#include "ring_chunk.h"

RingChunk::RingChunk(const size_t &ringBufferSize)
{
    chunkNumber = ringBufferSize;
    for (int i = 0; i < ringBufferSize; i++)
    {
        chunkArray.emplace_back(make_unique<CharChunk>(nearestPowerOfTwo(ringBufferSize)));
    }
}

void RingChunk::push(const char *var)
{
    std::unique_lock<std::mutex> lock(mutex_);
    cvPush.wait(lock, [this] { return !full(); });
    // 把当前内存写入内存块中[1]
    CharChunk *ptr;

    int strBegin = 0;
    int strEnd = strlen(var);
    // chunkArray[writeIndex & mask]->copyMemory(var, strBegin, strEnd);

    // 如果当前内存块满了，新申请一个内存块 [2]
    writeIndex.fetch_add(1, std::memory_order_release);
    cvPop.notify_one();
}

CharChunk *RingChunk::pop()
{
    std::unique_lock<std::mutex> lock(mutex_);
    cvPop.wait(lock, [this] { return !empty(); });

    CharChunk *item = chunkArray[readIndex & mask].get();
    readIndex.fetch_add(1, std::memory_order_acquire);
    cvPush.notify_one();
    return item;
}

bool RingChunk::writeToFile(FILE *fp) {}

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
