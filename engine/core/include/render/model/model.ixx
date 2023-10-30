#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <include/rhi/vertex.h>
#include <include/rhi/index.h>

export module Model;

import <vector>;

namespace ToolEngine
{
	export struct Model
	{
		std::vector<Vertex> vertices;
		std::vector<Index> indices;
	};
}