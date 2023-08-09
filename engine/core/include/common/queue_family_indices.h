#pragma once
#include <cstdint>
#include <optional>

namespace ToolEngine
{
    // queue is a container of gpu command, these indices mean which subset command this queue allow
    struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphics_family;
		std::optional<uint32_t> present_family;

		bool isComplete()
		{
			return graphics_family.has_value() && present_family.has_value();
		}
	};
}