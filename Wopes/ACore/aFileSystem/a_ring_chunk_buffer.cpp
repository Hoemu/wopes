#include "a_ring_chunk_buffer.h"

aRingChunkBuffer::aRingChunkBuffer(const int &size)
{
    producer = 0;
    consumer = 0;
    bufferBitSize = size * CHUNK_SIZE;
    bufferLen = size;
    for (int i = 0; i < bufferLen; ++i)
    {
        memoryBufferVector.emplace_back(std::make_unique<Chunk>(CHUNK_SIZE));
    }
}

aRingChunkBuffer::~aRingChunkBuffer()
{
    memoryBufferVector.clear();
}

void aRingChunkBuffer::append_buffer(const char *var)
{
    int len = strlen(var);

    // TODO 注意需要判断内存已经满了，是否还需要继续进行读取

    if (len < memoryBufferVector[producer]->remainder()) // 考虑情况，当写入内存小于一个内存块的时候
    {
        memoryCopy(var, len);
    }
    else
    {
        memoryBufferVector[producer]->full = true;
        producer = (producer + 1) % bufferLen;
        if (memoryBufferVector[producer]->full == true)
        {
            // 此时内存已经满了（要么进行延长等待，要么新加入一块内存）
            return;
        }
        memoryCopy(var, len);
    }
}

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

void aRingChunkBuffer::memoryCopy(const char *var, const size_t &len)
{
    memcpy(memoryBufferVector[producer]->buffer + memoryBufferVector[producer]->used, var, len);
    memoryBufferVector[producer]->used += len;
}
