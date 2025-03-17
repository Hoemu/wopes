#include "threadttest.h"

ThreadTtest::ThreadTtest(QObject *parent) : QThread(parent)
{
    isRunning = false;
}

void ThreadTtest::begin()
{
    isRunning = true;
    this->start();
}

void ThreadTtest::end()
{
    isRunning = false;
}

void ThreadTtest::run()
{
    while (isRunning)
    {
        test();
    }
}

void ThreadTtest::test()
{
    i++;
    LOG_ERROR("Test--:" + std::to_string(i));
}
