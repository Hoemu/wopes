#ifndef LOG_DEFINE_H
#define LOG_DEFINE_H

#define HAS_FILE_INFO

#include "log_system.h"

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
