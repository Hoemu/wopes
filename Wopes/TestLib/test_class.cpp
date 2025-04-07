#include "test_class.h"
#include <iostream>
#include "ring_chunk.h"

TestClass::TestClass()
{
    ringChunk = new RingChunk(3, 4);

    // rthead = std::thread(&TestClass::pushTread, this);
    // wthead = std::thread(&TestClass::popThread, this);
    // delete chTest;
    testRingChunk();
    // testChunk();

    // testChar();
    // testThread();
}

TestClass::~TestClass()
{
    // wthead.detach();
    // rthead.detach();
}

void TestClass::testRingChunk()
{
    RingChunk ringChunk(3, 4);

    const char *ch = "123456";
    char *tptr = nullptr;

    // for (int i = 0; i < 3; i++)
    // {
    //     ringChunk.try_push(ch);
    // }

    std::cout << "------------[begin]----------" << std::endl;
    // std::cout << "pop size:" << ringChunk.size() << "^ " << ringChunk.try_pop()->getMemroyChunk() << std::endl;
    ringChunk.try_push(ch);
    std::cout << "pop size:" << ringChunk.size() << "^ " << ringChunk.try_pop()->getMemroyChunk() << std::endl;
    ringChunk.try_push(ch);
    ringChunk.try_push(ch);
    std::cout << "pop size:" << ringChunk.size() << "^ " << ringChunk.try_pop()->getMemroyChunk() << std::endl;
    std::cout << "pop size:" << ringChunk.size() << "^ " << ringChunk.try_pop()->getMemroyChunk() << std::endl;
    ringChunk.try_push(ch);
    std::cout << "pop size:" << ringChunk.size() << "^ " << ringChunk.try_pop()->getMemroyChunk() << std::endl;
    // std::cout << " size:" << ringChunk.size() << "^ " << ringChunk.try_pop()->getMemroyChunk() << std::endl;
    // ringChunk.try_pop()->getMemroyChunk();
    // std::cout << " size:" << ringChunk.size() << "^ " << ringChunk.try_pop()->getMemroyChunk() << std::endl;
    // std::cout << " size:" << ringChunk.size() << "^ " << ringChunk.try_pop()->getMemroyChunk() << std::endl;
    std::cout << "-------------[end]-----------" << std::endl;
}

void TestClass::pushTread()
{
    int pushNumber = 100000;
    std::cout << "push thread begin." << std::endl;
    const char *ch = "123456";
    while (1)
    {
        ringChunk->try_push(ch);
    }
    // for (int i = 0; i < pushNumber; i++) {}
    std::cout << "push thread end." << std::endl;
}

void TestClass::popThread()
{
    std::cout << "pop thread begin." << std::endl;
    while (1)
    {
        ringChunk->try_pop();
    }
    std::cout << "pop thread begin." << std::endl;
}

void TestClass::testThread()
{
    // pushTread();
    // popThread();
    std::cout << LOG_INFO << ":" << std::endl;
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
