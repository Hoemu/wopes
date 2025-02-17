#ifndef LOG_DEFINE_H
#define LOG_DEFINE_H

#define HAS_FILE_INFO

#include "log_system.h"

#if defined(HAS_FILE_INFO)
#define LOG_INFO(x)                                                     \
    LogSystem::instance()->setLogMsg(__FILE__, __FUNCTION__, __LINE__); \
    LogSystem::instance()->setLogModel(LOG_LEVEL::LOG_INFO);            \
    LogSystem::instance()->setMsg(x);                                   \
    LogSystem::instance()->getControllerObject()
#define LOG_DEBUG(x)                                                    \
    LogSystem::instance()->setLogMsg(__FILE__, __FUNCTION__, __LINE__); \
    LogSystem::instance()->setLogModel(LOG_LEVEL::LOG_DEBUG);           \
    LogSystem::instance()->setMsg(x);                                   \
    LogSystem::instance()->getControllerObject()
#else
#define LOG_INFO(x)                                          \
    LogSystem::instance()->setLogModel(LOG_LEVEL::LOG_INFO); \
    LogSystem::instance()->setMsg(x)
#endif

#endif // LOG_DEFINE_H
