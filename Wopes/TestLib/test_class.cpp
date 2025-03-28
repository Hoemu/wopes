#include "test_class.h"

#include "ring_chunk.h"

TestClass::TestClass()
{
    // delete chTest;
    testRingChunk();
}

TestClass::~TestClass() {}

void TestClass::testRingChunk()
{
    RingChunk ringChunk(10);

    int getSize = ringChunk.getStoreSize();

    ringChunk.push("123456");
    ringChunk.push("123456");
    ringChunk.push("123456");

    std::cout << ringChunk.pop()->getMemroyChunk() << std::endl;
    std::cout << ringChunk.pop()->getMemroyChunk() << std::endl;
}

void TestClass::testChunk()
{
    char *ch = "12";
    char *chr = "34";
    char *chrr = "56";
    char *chrT = "123456";

    CharChunk chTest(4);

    std::cout << "back:" << chTest.copyMemory(chrT, 2, 6) << "]->" << std::endl;
    std::cout << chTest.getMemroyChunk() << ",  is full:" << chTest.isFull() << std::endl;
}
