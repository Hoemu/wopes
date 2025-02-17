#include "a_core.h"
#include <iostream>
#include "aLog/log_define.h"

ACore::ACore() {}

void ACore::print()
{
    std::cout << "print_F" << std::endl;
    LOG_INFO("init core.");
}

void ACore::test()
{
    std::cout << "test" << std::endl;
}

void ACore::build()
{
    std::cout << "build running..." << std::endl;
}
