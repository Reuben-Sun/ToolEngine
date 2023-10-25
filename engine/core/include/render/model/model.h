#pragma once

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <vector>
#include <include/rhi/vertex.h>
#include <include/rhi/index.h>

namespace ToolEngine
{
	struct Model
	{
		std::vector<Vertex> vertices;
		std::vector<Index> indices;
	};
}