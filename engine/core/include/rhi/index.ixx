#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <vulkan/vulkan.h>

export module Index;

import <vector>;
import <array>;

namespace ToolEngine
{
	/// <summary>
	/// The indices are arranged in a triangle list
	/// </summary>
	export struct Index
	{
		uint16_t index;
	};
}