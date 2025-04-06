#ifndef TEST_CLASS_H
#define TEST_CLASS_H

#include <thread>
#include "ring_chunk.h"

const char LOG_INFO[9] = "LOG_INFO";
const char LOG_DEBUG[10] = "LOG_DEBUG";
const char LOG_DETUALT[12] = "LOG_DETUALT";

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
