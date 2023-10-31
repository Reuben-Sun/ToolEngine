#include <vulkan/vulkan.h>
#include "device.h"

export module Buffer;

import Vertex;
import SingleTimeCommandBuffer;
import PhysicalDevice;

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