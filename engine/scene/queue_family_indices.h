#pragma once
#include <cstdint>
#include <optional>

namespace ToolEngine
{
    // queue is a container of gpu command, these indices mean which subset command this queue allow
    struct QueueFamilyIndices 
    {
        std::optional<uint32_t> graphicsFamily;

        bool isComplete() 
        {
            // C++17 feature, similar with NULL Object in Java
            return graphicsFamily.has_value();
        }
    };
}