#include <vulkan/vulkan.h>

export module BufferUtils;
import Device;
import PhysicalDevice;

namespace ToolEngine
{
	export class BufferUtils
	{
	public:
		static uint32_t findMemoryType(PhysicalDevice& physical_device, uint32_t type_filter, VkMemoryPropertyFlags properties);

		static void createBuffer(Device& device, PhysicalDevice& physical_device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& buffer_memory);

		static void copyBuffer(Device& device, VkBuffer src_buffer, VkBuffer dst_buffer, VkDeviceSize size);
	};
}