#pragma once

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <vector>
#include <array>

namespace ToolEngine
{
	struct Vertex
	{
		glm::vec3 pos;
		glm::vec3 color;
        glm::vec2 texture_coord;

        static VkVertexInputBindingDescription getBindingDescription() 
        {
            VkVertexInputBindingDescription binding_description{};
            binding_description.binding = 0;
            binding_description.stride = sizeof(Vertex);
            binding_description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return binding_description;
        }

        static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() 
        {
            std::array<VkVertexInputAttributeDescription, 3> attribute_descriptions{};
            // vertex object position
            attribute_descriptions[0].binding = 0;
            attribute_descriptions[0].location = 0;
            attribute_descriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
            attribute_descriptions[0].offset = offsetof(Vertex, pos);
            // proper color
            attribute_descriptions[1].binding = 0;
            attribute_descriptions[1].location = 1;
            attribute_descriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attribute_descriptions[1].offset = offsetof(Vertex, color);
            // uv0
            attribute_descriptions[2].binding = 0;
            attribute_descriptions[2].location = 2;
            attribute_descriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
            attribute_descriptions[2].offset = offsetof(Vertex, texture_coord);

            return attribute_descriptions;
        }
	};

    const std::vector<Vertex> VERTEX_BUFFER =
    {
        {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},

        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
    };

    const std::vector<uint16_t> INDEX_BUFFER = 
	{
         0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4
	};
}