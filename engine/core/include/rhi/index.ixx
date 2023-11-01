#include <vulkan/vulkan.h>

export module Index;

import <vector>;
import <array>;
import <glm/vec3.hpp>;
import <glm/mat4x4.hpp>;

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