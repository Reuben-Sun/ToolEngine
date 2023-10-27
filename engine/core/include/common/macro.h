#pragma once

#include "include/common/log_manager.h"
#include "include/global/global_context.h"


#define FORCEINLINE __forceinline

#define PI 3.1415926535897932384626433832795f

#define LOG_HELPER(LOG_LEVEL, MODULE, FMT_STRING, ...) \
    g_global_context.m_log_manager->log(LOG_LEVEL, MODULE##FMT_STRING, __VA_ARGS__);
/*#define LOG_HELPER(LOG_LEVEL, FMT_STRING, ...) \
    LOG_HELPER2(LOG_LEVEL, FMT_STRING, __VA_ARGS__)*/

#define LOG_DEBUG(...) LOG_HELPER(LogManager::LogLevel::Debug, __VA_ARGS__);

#define LOG_INFO(...) LOG_HELPER(LogManager::LogLevel::Info, __VA_ARGS__);

#define LOG_WARN(...) LOG_HELPER(LogManager::LogLevel::Warn, __VA_ARGS__);

#define LOG_ERROR(...) LOG_HELPER(LogManager::LogLevel::Error, __VA_ARGS__);

#define LOG_FATAL(...) LOG_HELPER(LogManager::LogLevel::Fatal, __VA_ARGS__);



