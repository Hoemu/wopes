#include "test_class.h"

#include <gtest/gtest.h>
#include <iostream>

using namespace std;

TEST(LogController, setConsoleCondition)
{
    TestClass tes;
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
