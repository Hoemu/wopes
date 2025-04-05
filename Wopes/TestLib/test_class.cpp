#include "test_class.h"

#include "ring_chunk.h"

TestClass::TestClass()
{
    // delete chTest;
    testRingChunk();
    // testChunk();

    // testChar();
}

TestClass::~TestClass() {}

void TestClass::testRingChunk()
{
    RingChunk ringChunk(10);

    const char *ch = "123456";
    char *tptr = nullptr;

    for (int i = 0; i < 2; i++)
    {
        ringChunk.push(ch);
    }

    int getSize = ringChunk.getStoreSize();

    std::cout << "------------[begin]----------" << std::endl;
    std::cout << " size:" << ringChunk.size() << "^ " << ringChunk.pop()->getMemroyChunk() << std::endl;
    std::cout << " size:" << ringChunk.size() << "^ " << ringChunk.pop()->getMemroyChunk() << std::endl;
    std::cout << " size:" << ringChunk.size() << "^ " << ringChunk.pop()->getMemroyChunk() << std::endl;
    std::cout << " size:" << ringChunk.size() << "^ " << ringChunk.pop()->getMemroyChunk() << std::endl;
    std::cout << " size:" << ringChunk.size() << "^ " << ringChunk.pop()->getMemroyChunk() << std::endl;
    std::cout << "-------------[end]-----------" << std::endl;
}

void TestClass::testChar()
{
    // std::cout << cr.getCChar();
}

void TestClass::testChunk()
{
    const char *ch = "12";
    const char *chr = "34";
    const char *chrr = "56";
    const char *chrT = "123456";

    CharChunk chTest(4);

    std::cout << "back:" << chTest.copyMemory("1234", 2, 6) << "]->" << std::endl;
    std::cout << chTest.getMemroyChunk() << ",  is full:" << chTest.isFull() << std::endl;
}
