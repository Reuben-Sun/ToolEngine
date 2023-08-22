#pragma once

#include <vulkan/vulkan.h>
#include "device.h"
#include "physical_device.h"
#include "vertex_descriptor.h"

namespace ToolEngine
{
	class Buffer
	{
	public:
		Buffer(Device& device, PhysicalDevice& physical_device);
		virtual ~Buffer() = default;

		VkBuffer getHandle() const { return m_buffer; }
	protected:
		VkBuffer m_buffer;
		VkDeviceMemory m_memory;
		Device& m_device;
		PhysicalDevice& m_physical_device;
		
		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
		void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		void copyBuffer(VkBuffer src_buffer, VkBuffer dst_buffer, VkDeviceSize size);
	};
}