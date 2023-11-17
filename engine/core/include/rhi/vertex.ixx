#include "include/common/macro.h"

export module Vertex;

namespace ToolEngine
{
	export struct Vertex
	{
		glm::vec3 pos;
		glm::vec3 color;
        glm::vec2 texture_coord;

        static VkVertexInputBindingDescription getBindingDescription();

		static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();
	};
}