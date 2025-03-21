#ifndef A_RING_CHUNK_BUFFER_H
#define A_RING_CHUNK_BUFFER_H

// 一定是2的n次幂
#define RINGBUFFSIZE 64
#define CHUNK_SIZE (1024 * 256)

#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdint>
#include <memory>
#include <vector>

using std::vector;

/**
 * @brief 内存块
 */
struct Chunk
{
    uint8_t *buffer; // 缓冲区指针
    size_t used;     // 被使用
    size_t capacity; // 缓冲区大小
    bool full;       // 缓冲区是否已满

    /** 当前内存块剩余内存 */
    size_t remainder() const
    {
        return capacity - used;
    };

    Chunk(size_t capacity_)
    {
        capacity = capacity_;
        used = 0;
        full = false;
        buffer = (uint8_t *)malloc(capacity);
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

    void append_buffer(const char *var);

    bool writeToDisk(FILE *fp);

protected:
    /** 内存拷贝 */
    void memoryCopy(const char *var, const size_t &len);

private:
    /** 内存缓冲向量 */
    vector<std::unique_ptr<Chunk>> memoryBufferVector; // 需要初始环状大小
    int producer;                                      // 内存生产者
    int consumer;                                      // 内存消费者
    int bufferBitSize;                                 // 缓冲大小
    int bufferLen;

    sem_t m_semWriteToDisk;
};

#endif // A_RING_CHUNK_BUFFER_H
