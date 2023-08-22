#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "buffer.h"
#include "device.h"
#include "physical_device.h"

namespace ToolEngine
{
	class VertexBuffer: public Buffer
	{
	public:
		VertexBuffer(Device& device, PhysicalDevice& physical_device, std::vector<Vertex> vertex_buffer);
		virtual ~VertexBuffer();
	private:
		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
		void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		void copyBuffer(VkBuffer src_buffer, VkBuffer dst_buffer, VkDeviceSize size);
	};
}