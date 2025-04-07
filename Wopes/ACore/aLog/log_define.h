#ifndef LOG_DEFINE_H
#define LOG_DEFINE_H

#define HAS_FILE_INFO
// #define Args args...

#include <stdio.h>
#include "log_system.h"

// 注意：每使用一次此宏，都会创建一个 while 循环

#if defined(HAS_FILE_INFO)
#define LOG_INFO                                                                     \
    LogSystem::instance()->setBaseMsg(__FILE__, __FUNCTION__, __LINE__, "LOG_INFO"); \
    LogSystem::instance()->setMessage
#define LOG_DEBUG                                                                     \
    LogSystem::instance()->setBaseMsg(__FILE__, __FUNCTION__, __LINE__, "LOG_DEBUG"); \
    LogSystem::instance()->setMessage
#define LOG_DETUALT                                                                     \
    LogSystem::instance()->setBaseMsg(__FILE__, __FUNCTION__, __LINE__, "LOG_DETUALT"); \
    LogSystem::instance()->setMessage
#define LOG_WARN                                                                     \
    LogSystem::instance()->setBaseMsg(__FILE__, __FUNCTION__, __LINE__, "LOG_WARN"); \
    LogSystem::instance()->setMessage
#define LOG_ERROR                                                                     \
    LogSystem::instance()->setBaseMsg(__FILE__, __FUNCTION__, __LINE__, "LOG_ERROR"); \
    LogSystem::instance()->setMessage
#define LOG_FATAL                                                                     \
    LogSystem::instance()->setBaseMsg(__FILE__, __FUNCTION__, __LINE__, "LOG_FATAL"); \
    LogSystem::instance()->setMessage
#else
#define LOG_INFO(x)                                          \
    LogSystem::instance()->setLogModel(LOG_LEVEL::LOG_INFO); \
    LogSystem::instance()->setMsg(x)
#endif

#endif // LOG_DEFINE_H
