#pragma once

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <vector>
#include <array>

namespace ToolEngine
{
	/// <summary>
	/// The indices are arranged in a triangle list
	/// </summary>
	struct Index
	{
		uint16_t index;
	};

	const std::vector<Index> INDEX_BUFFER =
	{
		{0}, {1}, {2}, {2}, {3}, {0},
		{4}, {5}, {6}, {6}, {7}, {4}
	};
}