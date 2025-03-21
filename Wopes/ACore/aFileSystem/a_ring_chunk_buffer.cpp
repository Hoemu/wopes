#include "a_ring_chunk_buffer.h"

aRingChunkBuffer::aRingChunkBuffer(const int &size)
{
    writePos = 0;
    readPos = 0;
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

void aRingChunkBuffer::append_buffer(char *var)
{
    strlen(var);
}
