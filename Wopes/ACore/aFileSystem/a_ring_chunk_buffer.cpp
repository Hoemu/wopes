#include "a_ring_chunk_buffer.h"

#include <stdexcept>

aRingChunkBuffer::aRingChunkBuffer(int size) : m_nProducePos(0), m_nConsumerPos(0), m_nBuffSize(size)
{
    memoryBufferVector.resize(size);
    sem_init(&m_semWriteToDisk, 0, 0);
}

aRingChunkBuffer::~aRingChunkBuffer()
{
    sem_destroy(&m_semWriteToDisk);
}

int aRingChunkBuffer::getProducePos()
{
    return m_nProducePos & (m_nBuffSize - 1);
}

int aRingChunkBuffer::getConsumerPos()
{
    return m_nConsumerPos & (m_nBuffSize - 1);
}

void aRingChunkBuffer::incProducePos()
{
    m_nProducePos = (m_nProducePos + 1) & (m_nBuffSize - 1); // 1 & 1
}

void aRingChunkBuffer::incConsumerPos()
{
    m_nConsumerPos = (m_nConsumerPos + 1) & (m_nBuffSize - 1);
}

void aRingChunkBuffer::appendToBuff(const char* data, const int length)
{
    if (length == 0 || data == nullptr)
    {
        return;
        // throw std::runtime_error(" appendToBuff fail ! check your length or data !");
    }

    // 全部的chunk都满时会发生写不进的问题
    // 如果当前写入内存小于当前内存块，读入信息
    if (memoryBufferVector[m_nProducePos].m_u32Used + length <= memoryBufferVector[m_nProducePos].m_u32Cap)
    {
        memcpy(memoryBufferVector[m_nProducePos].m_cMemory + memoryBufferVector[m_nProducePos].m_u32Used, data, length);
        memoryBufferVector[m_nProducePos].m_u32Used += length;
    }
    else //
    {
        memoryBufferVector[m_nProducePos].m_u32Flag = true;
        incProducePos();
        sem_post(&m_semWriteToDisk); // 信号量 + 1
        if (memoryBufferVector[m_nProducePos].m_u32Flag == true)
        {
            // std::cout << " RingBuff filled ! reset your RingBUff size !" << std::endl;
            throw std::runtime_error(" RingBuff filled ! reset your RingBUff size !");
        }
        else
        {
            memcpy(memoryBufferVector[m_nProducePos].m_cMemory + memoryBufferVector[m_nProducePos].m_u32Used, data, length);
            memoryBufferVector[m_nProducePos].m_u32Used += length;
        }
        // appendToBuff(data, length);
    }
}

void aRingChunkBuffer::writeToDisk(FILE* fp)
{
    if (memoryBufferVector[m_nConsumerPos].m_u32Flag == true)
    {
        uint32_t wt_len = fwrite(memoryBufferVector[m_nConsumerPos].m_cMemory, 1, memoryBufferVector[m_nConsumerPos].m_u32Used, fp);
        if (wt_len != memoryBufferVector[m_nConsumerPos].m_u32Used)
        {
            throw std::runtime_error(" fwrite fail ! ");
        }

        fflush(fp);
        memoryBufferVector[m_nConsumerPos].m_u32Flag = false;
        memoryBufferVector[m_nConsumerPos].m_u32Used = 0;
        incConsumerPos();
    }
}

void aRingChunkBuffer::forceWriteToDisk(FILE* fp)
{
    // 防止程序结束后未标记为满的chunk 丢失，强制写入磁盘
    for (int i = 0; i < RINGBUFFSIZE; ++i)
    {
        if (memoryBufferVector[m_nConsumerPos].m_u32Used != 0)
        {
            uint32_t wt_len = fwrite(memoryBufferVector[m_nConsumerPos].m_cMemory, 1, memoryBufferVector[m_nConsumerPos].m_u32Used, fp);
            if (wt_len != memoryBufferVector[m_nConsumerPos].m_u32Used)
            {
                throw std::runtime_error(" fwrite fail ! ");
            }
            fflush(fp);
            memoryBufferVector[m_nConsumerPos].m_u32Used = 0;
            incConsumerPos();
        }
        else
        {
            // sem_close(&m_semWriteToDisk);
            break;
        }
    }
}

sem_t& aRingChunkBuffer::getSemWriteToDisk()
{
    return m_semWriteToDisk;
}
