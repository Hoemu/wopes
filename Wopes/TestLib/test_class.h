#ifndef TEST_CLASS_H
#define TEST_CLASS_H

#include <thread>
#include "ring_chunk.h"

class TestClass
{
public:
    TestClass();
    ~TestClass();

    void testChunk();

    void testRingChunk();

    void pushTread();

    void popThread();

    void testThread();

    void testChar();

private:
    RingChunk *ringChunk;

    std::thread rthead;
    std::thread wthead;
};

#endif // TEST_CLASS_H
