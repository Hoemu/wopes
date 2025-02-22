#include <iostream>
#include "./aLog/log_define.h"

int main()
{
    LOG_INFO("main:");
    std::cout << "hello world." << std::endl;
    return 0;
}
