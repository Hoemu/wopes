#include "ring_chunk.h"

RingChunk::RingChunk(const size_t &ringBufferSize)
{
    readIndex.store(0);
    writeIndex.store(0);

    chunkNumber = nearestPowerOfTwo(ringBufferSize);
    for (int i = 0; i < ringBufferSize; i++)
    {
        chunkArray.push_back(make_unique<CharChunk>(chunkNumber));
    }

    mask = ringBufferSize - 1;
    storeSize = chunkNumber * chunkNumber;
}

void RingChunk::push(const char *var) noexcept
{
    // std::unique_lock<std::mutex> lock(mutex_);
    // cvPush.wait(lock, [this] { return !full(); });

    int strPos = 0;
    int strEnd = strlen(var);
    char *ptr = nullptr;
    int writeIndexCp;

    while (writeIndex < strEnd && strPos < strEnd)
    {
        int tre = writeIndex & mask;
        strPos = chunkArray[writeIndex & mask]->copyMemory(var, strPos, strEnd);
        if (chunkArray[writeIndex & mask]->isFull())
        {
            writeIndex.fetch_add(1, std::memory_order_release);
        }
    }

    // writeEndFill.store(chunkArray[writeIndex & mask]->isFull(), std::memory_order_release);

    // 如果当前内存块满了，新申请一个内存块 [2]
    // cvPop.notify_one();
}

CharChunk *RingChunk::pop()
{
    // if (size() <= 0)
    // {
    //     throw std::runtime_error("Ring buffer is empty, pop fail!");
    //     return nullptr;
    // }
    // std::unique_lock<std::mutex> lock(mutex_);
    // cvPop.wait(lock, [this] { return !empty(); });
    // TODO 需要判断是否已经为空了
    CharChunk *ptr = chunkArray[readIndex & mask].get();
    chunkArray[readIndex & mask]->resetMemory();

    readIndex.fetch_add(1, std::memory_order_acquire);

    // cvPush.notify_one();
    return ptr;
}

unsigned int RingChunk::getStoreSize() const
{
    return storeSize;
}

inline size_t RingChunk::size() const
{
    return writeIndex.load(std::memory_order_acquire) + chunkArray[writeIndex & mask]->isFull() - readIndex.load(std::memory_order_acquire);
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
