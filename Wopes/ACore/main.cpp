#include <iostream>
#include "./aLog/log_define.h"

int main()
{
    LOG_INFO("main:");
    std::cout << "hello world." << std::endl;

    while (1) {} // 需要线程阻塞
    return 0;
}
