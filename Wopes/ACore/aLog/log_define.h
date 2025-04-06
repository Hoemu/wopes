#ifndef LOG_DEFINE_H
#define LOG_DEFINE_H

#define HAS_FILE_INFO

#include <stdio.h>
#include "log_system.h"
extern "C"
{
// 注意：每使用一次此宏，都会创建一个 while 循环
#define TEST_LOG(fmt, args...)                                                              \
    {                                                                                       \
        LogSystem::instance()->setBaseMsg(__FILE__, __FUNCTION__, __LINE__, LOG_INFO_CHAR); \
        LogSystem::instance()->setMessage(fmt, ##args);                                     \
    }
}

#define LOG_TEST_CLASS log::instance->setMessage(__FILE__, __FUNCTION__, __LINE__, ##args)

#if defined(HAS_FILE_INFO)
#define LOG_INFO                                                        \
    LogSystem::instance()->setLogMsg(__FILE__, __FUNCTION__, __LINE__); \
    LogSystem::instance()->setLogModel(LOG_LEVEL::LOG_INFO);            \
    LogSystem::instance()->setMsg
#define LOG_DEBUG                                                       \
    LogSystem::instance()->setLogMsg(__FILE__, __FUNCTION__, __LINE__); \
    LogSystem::instance()->setLogModel(LOG_LEVEL::LOG_DEBUG);           \
    LogSystem::instance()->setMsg
#define LOG_DETUALT                                                     \
    LogSystem::instance()->setLogMsg(__FILE__, __FUNCTION__, __LINE__); \
    LogSystem::instance()->setLogModel(LOG_LEVEL::LOG_DETUALT);         \
    LogSystem::instance()->setMsg
#define LOG_WARN                                                        \
    LogSystem::instance()->setLogMsg(__FILE__, __FUNCTION__, __LINE__); \
    LogSystem::instance()->setLogModel(LOG_LEVEL::LOG_WARN);            \
    LogSystem::instance()->setMsg
#define LOG_ERROR                                                       \
    LogSystem::instance()->setLogMsg(__FILE__, __FUNCTION__, __LINE__); \
    LogSystem::instance()->setLogModel(LOG_LEVEL::LOG_ERROR);           \
    LogSystem::instance()->setMsg
#define LOG_FATAL                                                       \
    LogSystem::instance()->setLogMsg(__FILE__, __FUNCTION__, __LINE__); \
    LogSystem::instance()->setLogModel(LOG_LEVEL::LOG_FATAL);           \
    LogSystem::instance()->setMsg
#else
#define LOG_INFO(x)                                          \
    LogSystem::instance()->setLogModel(LOG_LEVEL::LOG_INFO); \
    LogSystem::instance()->setMsg(x)
#endif

#endif // LOG_DEFINE_H
