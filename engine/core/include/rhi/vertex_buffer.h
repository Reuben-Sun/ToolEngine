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
		VkBuffer getHandle() const { return m_buffer; }
	private:
		VkBuffer m_buffer;
		VkDeviceMemory m_memory;
	};
}