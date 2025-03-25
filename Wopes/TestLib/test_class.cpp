#include "test_class.h"

#include "ring_chunk.h"

TestClass::TestClass()
{
    char *ch = "123456789";

    CharChunk *chTest = new CharChunk(4);

    // chTest->copyMemory("ch", 0, strlen(ch));

    delete chTest;
}

TestClass::~TestClass() {}
