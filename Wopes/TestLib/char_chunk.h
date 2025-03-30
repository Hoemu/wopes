#ifndef CHAR_CHUNK_H
#define CHAR_CHUNK_H

#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <vector>

using cstr = const char *; // 增强代码可读性

using std::make_unique;
using std::unique_ptr;
using std::vector;

class CharChunk
{
public:
    CharChunk(size_t len);

    ~CharChunk();

    /** 深拷贝 */
    CharChunk(const CharChunk &other);

    /** 返回读指针，如果字符串读取完毕，返回最后长度 */
    int copyMemory(const char *var, const int &chBeign, const int &chEnd);

    char *getMemroyChunk() const;

    bool isFull() const;

    void resetMemory();

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
