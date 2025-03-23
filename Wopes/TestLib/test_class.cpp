#include "test_class.h"

#include "ring_chunk.h"

TestClass::TestClass()
{
    RingChunk *chTest = new RingChunk(100);

    chTest->push("fdas");

    delete chTest;
}

TestClass::~TestClass() {}
