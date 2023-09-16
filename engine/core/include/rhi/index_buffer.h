#pragma once

#include <vector>
#include <vulkan/vulkan.h>
#include "buffer.h"

namespace ToolEngine
{
	class IndexBuffer : public Buffer
	{
	public:
		IndexBuffer(Device& device, PhysicalDevice& physical_device, std::vector<uint16_t> index_buffer);
		virtual ~IndexBuffer();
		VkBuffer getHandle() const { return m_buffer; }
	private:
		VkBuffer m_buffer;
		VkDeviceMemory m_memory;
	};
}