#ifndef A_RING_CHUNK_BUFFER_H
#define A_RING_CHUNK_BUFFER_H

// 一定是2的n次幂
#define RINGBUFFSIZE 64
#define CHUNKMEMSIZE (1024 * 256)
#define FULL 1
#define NOTFULL 0

#include <semaphore.h>
#include <stdio.h>
#include <cstdint>
#include <vector>

using std::vector;

/**
 * @brief 内存块
 */
struct Chunk
{
    uint32_t m_u32Cap;
    uint32_t m_u32Used;
    uint32_t m_u32Flag;
    char *m_cMemory;

    Chunk() : m_u32Cap(CHUNKMEMSIZE), m_u32Used(0), m_u32Flag(NOTFULL)
    {
        m_cMemory = new char[CHUNKMEMSIZE];
    }

    ~Chunk()
    {
        do
        {
            if (m_cMemory != nullptr)
            {
                delete m_cMemory;
                m_cMemory = nullptr;
            }
        } while (false);
    }
};

/**
 * @brief 环形类
 */
class aRingChunkBuffer
{
public:
    explicit aRingChunkBuffer(const int size = RINGBUFFSIZE);

    ~aRingChunkBuffer();

    int getProducePos();

    int getConsumerPos();

    void incProducePos();

    void incConsumerPos();

    void appendToBuff(const char *data, const int length);

    void writeToDisk(FILE *fp);

    void forceWriteToDisk(FILE *fp);

    sem_t &getSemWriteToDisk();

private:
    std::vector<Chunk> m_vecBuff;
    int m_nProducePos;  // 更改只在appendToBuf,而该函数进入前是上锁的
    int m_nConsumerPos; // 单线程改变
    int m_nBuffSize;

    sem_t m_semWriteToDisk;
};

#endif // A_RING_CHUNK_BUFFER_H
