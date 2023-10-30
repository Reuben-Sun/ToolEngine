#include <vulkan/vulkan.h>
#include "device.h"
#include "physical_device.h"
#include "single_time_command_buffer.h"

export module Buffer;

import Vertex;

namespace ToolEngine
{
	export class Buffer
	{
	public:
		Buffer(Device& device, PhysicalDevice& physical_device);
		virtual ~Buffer() = default;

	protected:
		
		Device& m_device;
		PhysicalDevice& m_physical_device;
		
		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
		void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		void copyBuffer(VkBuffer src_buffer, VkBuffer dst_buffer, VkDeviceSize size);
	};
}