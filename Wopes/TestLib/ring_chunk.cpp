#include "ring_chunk.h"
#include <iostream>

RingChunk::RingChunk(const size_t &ringBufferSize, const size_t &chunkSizeVar)
{
    readIndex.store(0);
    writeIndex.store(0);

    singleChunk = make_unique<CharChunk>(chunkSizeVar);
    chunkNumber = nearestPowerOfTwo(ringBufferSize);
    for (int i = 0; i < chunkNumber; i++)
    {
        chunkArray.push_back(make_unique<CharChunk>(chunkSizeVar)); // 不调用 nearestPowerOfTwo（可能会增大内存）
    }

    mask = nearestPowerOfTwo(ringBufferSize) - 1;
    storeSize = chunkNumber * chunkNumber;

    std::cout << "init:"
              << " chunkNumber:" << chunkNumber << " mask:" << mask << ", storeSize:" << storeSize << "\n\n";
}

void RingChunk::try_push(const char *var) noexcept
{
    // writeIndex.load(std::memory_order_acquire);
    int strPos = 0;
    int strEnd = strlen(var);

    while ((writeIndex & mask) < chunkNumber && strPos < strEnd)
    {
        strPos = chunkArray[writeIndex & mask]->copyMemory(var, strPos, strEnd);
        std::cout << "push:" << chunkArray[writeIndex & mask].get()->getMemroyChunk() << "\n writeIndex:" << writeIndex << " strPos:" << strPos
                  << " writeIndex & mask:" << (writeIndex & mask) << std::endl;

        if (chunkArray[writeIndex & mask]->isFull())
        {
            writeIndex.fetch_add(1);
            if (chunkArray[writeIndex & mask]->isFull())
            {
                std::cout << "Queue is full, push of back is invalid, read notify, [read]:" << readIndex << std::endl;
                break;
            }
            std::cout << std::endl;
        }
    }
}

CharChunk *RingChunk::try_pop()
{
    if (readIndex == writeIndex)
    {
        std::cout << "Queue is empty, pop is invalid, write notify, [write]:" << writeIndex << std::endl;
        return nullptr;
    }

    readIndex.fetch_add(1);
    CharChunk *ptr = chunkArray[readIndex & mask].get();
    chunkArray[readIndex & mask]->resetMemory();
    // writeIndex.notify_one();

    return ptr;
}

void RingChunk::writeToFile(const char *var, FILE *fp)
{
    int strPos = 0;
    int strEnd = strlen(var);

    while ((writeIndex & mask) < chunkNumber && strPos < strEnd)
    {
        strPos = chunkArray[writeIndex & mask]->copyMemory(var, strPos, strEnd);

        if (chunkArray[writeIndex & mask]->isFull())
        {
            fwrite(chunkArray[writeIndex & mask]->getMemroyChunk(), chunkArray[writeIndex & mask]->size(), 1, fp);
            writeIndex.fetch_add(1);
            if (chunkArray[writeIndex & mask]->isFull())
            {
                break;
            }
        }
    }
}

unsigned int RingChunk::capacity() const
{
    return storeSize;
}

inline size_t RingChunk::size() const
{
    return writeIndex.load() + chunkArray[writeIndex & mask]->isFull() - readIndex.load();
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
