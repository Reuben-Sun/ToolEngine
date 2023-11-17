#include "include/common/macro.h"
import BufferUtils;
import Device;
import PhysicalDevice;
import SingleTimeCommandBuffer;

namespace ToolEngine
{
	uint32_t BufferUtils::findMemoryType(PhysicalDevice& physical_device, uint32_t type_filter, VkMemoryPropertyFlags properties)
	{
		VkPhysicalDeviceMemoryProperties mem_properties;
		vkGetPhysicalDeviceMemoryProperties(physical_device.getHandle(), &mem_properties);

		for (uint32_t i = 0; i < mem_properties.memoryTypeCount; i++)
		{
			if ((type_filter & (1 << i)) && (mem_properties.memoryTypes[i].propertyFlags & properties) == properties)
			{
				return i;
			}
		}
		LOG_ERROR("failed to find suitable memory type!");
		return 0;
	}
	void BufferUtils::createBuffer(Device& device, PhysicalDevice& physical_device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& buffer_memory)
	{
		VkBufferCreateInfo buffer_info{};
		buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		buffer_info.size = size;
		buffer_info.usage = usage;
		buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateBuffer(device.getHandle(), &buffer_info, nullptr, &buffer) != VK_SUCCESS)
		{
			LOG_ERROR("failed to create vertex buffer!");
		}

		VkMemoryRequirements mem_requirements;
		vkGetBufferMemoryRequirements(device.getHandle(), buffer, &mem_requirements);

		VkMemoryAllocateInfo alloc_info{};
		alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		alloc_info.allocationSize = mem_requirements.size;
		alloc_info.memoryTypeIndex = findMemoryType(physical_device, mem_requirements.memoryTypeBits, properties);

		if (vkAllocateMemory(device.getHandle(), &alloc_info, nullptr, &buffer_memory) != VK_SUCCESS)
		{
			LOG_ERROR("failed to allocate vertex buffer memory!");
		}

		vkBindBufferMemory(device.getHandle(), buffer, buffer_memory, 0);
	}
	void BufferUtils::copyBuffer(Device& device, VkBuffer src_buffer, VkBuffer dst_buffer, VkDeviceSize size)
	{
		std::unique_ptr<SingleTimeCommandBuffer> command_buffer = std::make_unique<SingleTimeCommandBuffer>(device);
		VkBufferCopy copyRegion{};
		copyRegion.size = size;
		vkCmdCopyBuffer(command_buffer->getHandle(), src_buffer, dst_buffer, 1, &copyRegion);
	}
}