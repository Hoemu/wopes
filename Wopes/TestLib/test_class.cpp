#include "test_class.h"

#include "ring_chunk.h"

TestClass::TestClass()
{
    char *ch = "12";
    char *chr = "34";
    char *chrr = "56";
    char *chrT = "123456";

    CharChunk chTest(4);

    std::cout << "back:" << chTest.copyMemory(chrT, 2, 6) << "]->" << std::endl;
    // std::cout << "back:" << chTest->copyMemory(chr, 0, 2) << "]->" << std::endl;
    // std::cout << "back:" << chTest->copyMemory(chrr, 0, 2) << "]->" << std::endl;

    std::cout << chTest.getMemroyChunk() << ",  is full:" << chTest.isFull() << std::endl;

    // delete chTest;
}

TestClass::~TestClass() {}
