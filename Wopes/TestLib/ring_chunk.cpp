#include "ring_chunk.h"
#include <iostream>

RingChunk::RingChunk(const size_t &ringBufferSize, const size_t &chunkSizeVar)
{
    readIndex.store(0);
    writeIndex.store(0);

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

void RingChunk::push(const char *var) noexcept
{
    writeIndex.load(std::memory_order_acquire);
    int strPos = 0;
    int strEnd = strlen(var);
    char *ptr = nullptr;
    int writeIndexCp;

    while (writeIndex < chunkNumber && strPos < strEnd)
    {
        strPos = chunkArray[writeIndex & mask]->copyMemory(var, strPos, strEnd);
        std::cout << "push:" << chunkArray[writeIndex & mask].get()->getMemroyChunk() << "\n writeIndex:" << writeIndex << " strPos:" << strPos
                  << " writeIndex & mask:" << (writeIndex & mask) << std::endl;

        if (chunkArray[writeIndex & mask]->isFull())
        {
            writeIndex.fetch_add(1, std::memory_order_release);

            // push 失败，会返回上一个内存块
            if (chunkArray[writeIndex & mask]->isFull())
            {
                readIndex.notify_one();
                writeIndex.fetch_sub(1);
                std::cout << "Queue is full, push of back is invalid, read notify, [read]:" << readIndex << std::endl;
                // throw std::runtime_error("Queue is full, push of back is invalid, [read]:");
                writeIndex.wait(writeIndex.load(std::memory_order_relaxed));
                break; // NOTE 可能不生效
            }
            std::cout << std::endl;
        }
    }
}

CharChunk *RingChunk::pop()
{
    if (readIndex == writeIndex)
    {
        writeIndex.notify_one();
        std::cout << "Queue is empty, pop is invalid, write notify, [write]:" << writeIndex << std::endl;
        // throw std::runtime_error("Queue is empty, pop is invalid!");
        readIndex.wait(readIndex.load(std::memory_order_relaxed));
    }

    readIndex.load(std::memory_order_acquire);
    CharChunk *ptr = chunkArray[readIndex & mask].get();
    chunkArray[readIndex & mask]->resetMemory();
    readIndex.fetch_add(1, std::memory_order_release);

    return ptr;
}

unsigned int RingChunk::capacity() const
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
