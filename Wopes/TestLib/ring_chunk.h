#ifndef RING_CHUNK_H
#define RING_CHUNK_H

#include <atomic>
#include "char_chunk.h"

class RingChunk
{
public:
    explicit RingChunk(const size_t &ringBufferSize, const size_t &chunkSizeVar);

    /** 阻塞式 */
    void try_push(const char *var) noexcept;

    /** 阻塞式 */
    CharChunk *try_pop();

    void writeToFile(const char *var, FILE *fp);

    unsigned int capacity() const;

    // 当前元素数量（线程安全）
    size_t size() const;

    bool full() const;
    bool empty() const;

protected:
    size_t nearestPowerOfTwo(size_t n) const;

private:
    /** 内存块数量 */
    size_t chunkNumber;
    /** 内存总大小 */
    size_t storeSize;

    unique_ptr<CharChunk> singleChunk;

    size_t mask;

    std::mutex mMutex;

    std::atomic<size_t> readIndex;  // 读指针（原子操作保证可见性）
    std::atomic<size_t> writeIndex; // 写指针

    vector<unique_ptr<CharChunk>> chunkArray;
};

#endif // RING_CHUNK_H
