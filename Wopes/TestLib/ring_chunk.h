#ifndef RING_CHUNK_H
#define RING_CHUNK_H

#include <atomic>
#include <condition_variable>
#include "char_chunk.h"

class RingChunk
{
public:
    explicit RingChunk(const size_t &ringBufferSize);

    /** 阻塞式 */
    void push(char *var) noexcept;

    /** 阻塞式 */
    CharChunk *pop();

    unsigned int getStoreSize() const;

    // 当前元素数量（线程安全）
    size_t size() const;

    bool full() const;
    bool empty() const;

protected:
    size_t nearestPowerOfTwo(size_t n) const;

private:
    size_t chunkNumber;
    size_t storeSize;

    size_t mask;
    mutable std::mutex mutex_; // 互斥锁

    int readTm = 0;
    int writeTm = 0;
    int lenMask;

    std::atomic<size_t> readIndex;  // 读指针（原子操作保证可见性）
    std::atomic<size_t> writeIndex; // 写指针

    std::condition_variable cvPush; // 写入条件变量
    std::condition_variable cvPop;  // 读取条件变量

    vector<unique_ptr<CharChunk>> chunkArray;
};

#endif // RING_CHUNK_H
