#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "device.h"
#include "physical_device.h"

import Buffer;
import Vertex;

namespace ToolEngine
{
	class VertexBuffer: public Buffer
	{
	public:
		VertexBuffer(Device& device, PhysicalDevice& physical_device, std::vector<Vertex> vertex_buffer);
		virtual ~VertexBuffer();
		void updateBuffer(std::vector<Vertex> vertex_buffer);
		VkBuffer getHandle() const { return m_buffer; }
	private:
		VkBuffer m_buffer;
		VkDeviceMemory m_memory;
		void* m_vertex_buffer_mapped;
	};
}