#include "a_ring_chunk_buffer.h"

aRingChunkBuffer::aRingChunkBuffer(const int &bufferArrarySize)
{
    producer = 0;
    consumer = 0;
    chunkSize = nearestPowerOfTwo(bufferArrarySize);
    bufferLen = bufferArrarySize;
    for (int i = 0; i < bufferLen; ++i)
    {
        memoryBufferVector.emplace_back(std::make_unique<Chunk>(chunkSize));
    }
}

aRingChunkBuffer::~aRingChunkBuffer()
{
    memoryBufferVector.clear();
}

bool aRingChunkBuffer::try_push(const char *var) {}

char *aRingChunkBuffer::pop() {}

char *aRingChunkBuffer::try_pop() {}

bool aRingChunkBuffer::writeToDisk(FILE *fp)
{
    if (memoryBufferVector[consumer]->full == true)
    {
        uint32_t wt_len = fwrite(memoryBufferVector[consumer]->buffer, 1, memoryBufferVector[consumer]->used, fp);
        if (wt_len != memoryBufferVector[consumer]->used)
        {
            // throw std::runtime_error(" fwrite fail ! ");
            return false;
        }

        fflush(fp);
        memoryBufferVector[consumer]->full = false;
        memoryBufferVector[consumer]->used = 0;
        consumer = (consumer + 1) % bufferLen;
    }
    return true;
}

inline void aRingChunkBuffer::memoryCopy(const char *var, const size_t &len)
{
    memcpy(memoryBufferVector[producer]->buffer + memoryBufferVector[producer]->used, var, len);
    memoryBufferVector[producer]->used += len;
}

inline size_t aRingChunkBuffer::nearestPowerOfTwo(size_t n) const
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
