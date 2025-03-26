#ifndef CHAR_CHUNK_H
#define CHAR_CHUNK_H

#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <vector>

using std::make_unique;
using std::unique_ptr;
using std::vector;

class CharChunk
{
public:
    CharChunk(size_t len)
    {
        memorySize = len;
        remainingMemory = len;
        readPtr = 0;
        memoryChunk = (char *)malloc(len + 1);

        if (!memoryChunk)
        {
            throw std::bad_alloc(); // 或通过其他方式处理异常
        }
    };
    ~CharChunk()
    {
        if (memoryChunk)
        {
            free(memoryChunk);
            memoryChunk = nullptr; // 防止重复释放
        }
    };

    /** 深拷贝 */
    CharChunk(const CharChunk &other);

    /** 返回读指针，如果字符串读取完毕，返回最后长度 */
    int copyMemory(char *var, const int &chBeign, const int &chEnd);

    char *getMemroyChunk();

    bool isFull() const;

private:
    /** 变量 */
    char *memoryChunk;

    /** 内存大小 */
    int memorySize;

    /** 读取指针 */
    int readPtr;

    /** 剩余内存 */
    int remainingMemory;
};

#endif // CHAR_CHUNK_H
