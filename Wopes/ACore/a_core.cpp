#include "a_core.h"
#include <iostream>

ACore::ACore() {}

void ACore::print()
{
    std::cout << "print_F" << std::endl;
}

void ACore::test()
{
    std::cout << "test" << std::endl;
}

void ACore::build()
{
    std::cout << "build running..." << std::endl;
}
