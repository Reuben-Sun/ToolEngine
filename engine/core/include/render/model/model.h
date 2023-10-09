#pragma once

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <vector>
#include <include/rhi/vertex.h>
#include <include/rhi/index.h>

namespace ToolEngine
{
	// TODO: this is a struct, which load and store the gltf
	// this model is not vulkan resource, we will use this to create buffer in pipeline
	struct Model
	{
		std::vector<Vertex> vertices;
		std::vector<Index> indices;
	};
}