#ifndef A_RING_CHUNK_BUFFER_H
#define A_RING_CHUNK_BUFFER_H

// 一定是2的n次幂
#define RINGBUFFSIZE 64
#define CHUNKMEMSIZE (1024 * 256)

#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdint>
#include <vector>

using std::vector;

/**
 * @brief 内存块
 */
struct Chunk
{
    uint8_t *buffer;   // 缓冲区指针
    size_t writePtr;   // 写指针
    size_t readPtr;    // 读指针
    size_t bufferSize; // 缓冲区大小
    bool full;         // 缓冲区是否已满

    Chunk(size_t bufferSize_)
    {
        bufferSize = bufferSize_;
        writePtr = 0;
        readPtr = 0;
        full = false;
        buffer = (uint8_t *)malloc(bufferSize_);
    }

    ~Chunk()
    {
        free(buffer);
    }
};

/**
 * @brief 环形类
 */
class aRingChunkBuffer
{
public:
    explicit aRingChunkBuffer(const int &size);

    ~aRingChunkBuffer();

private:
    /** 内存缓冲向量 */
    vector<Chunk> memoryBufferVector; // 需要初始环状大小
    int m_nProducePos;                // 更改只在appendToBuf,而该函数进入前是上锁的
    int m_nConsumerPos;               // 单线程改变
    int m_nBuffSize;                  // 缓冲大小

    sem_t m_semWriteToDisk;
};

#endif // A_RING_CHUNK_BUFFER_H
