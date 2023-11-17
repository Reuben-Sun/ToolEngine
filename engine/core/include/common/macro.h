#pragma once
#include <iostream>
#include <format>
#include <array>
#include <vector>
#include <memory>
#include <set>
#include <unordered_map>
#include <string>
#include <optional>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <math.h>
#include <regex>

#include <vulkan/vulkan.h>
#include <optick.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>

import LogManager;

#define FORCEINLINE __forceinline

#define LOG_HELPER(LOG_LEVEL, ...) \
    LogManager::getInstance().log(LOG_LEVEL,"[" __FUNCTION__ "] " +std::format(__VA_ARGS__));

#define LOG_DEBUG(...) LOG_HELPER(LogManager::LogLevel::Debug, __VA_ARGS__);

#define LOG_INFO(...) LOG_HELPER(LogManager::LogLevel::Info, __VA_ARGS__);

#define LOG_WARN(...) LOG_HELPER(LogManager::LogLevel::Warn, __VA_ARGS__);

#define LOG_ERROR(...) LOG_HELPER(LogManager::LogLevel::Error, __VA_ARGS__);

#define LOG_FATAL(...) LOG_HELPER(LogManager::LogLevel::Fatal, __VA_ARGS__);



