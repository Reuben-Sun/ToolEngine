#include <vulkan/vulkan.h>
#include "include/rhi/device.h"
#include "include/rhi/physical_device.h"
#include "include/rhi/single_time_command_buffer.h"
#include "include/common/macro.h"
import Buffer;

namespace ToolEngine
{
	Buffer::Buffer(Device& device, PhysicalDevice& physical_device): m_device(device), m_physical_device(physical_device)
	{
	}

	uint32_t Buffer::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
	{
		VkPhysicalDeviceMemoryProperties mem_properties;
		vkGetPhysicalDeviceMemoryProperties(m_physical_device.getHandle(), &mem_properties);

		for (uint32_t i = 0; i < mem_properties.memoryTypeCount; i++)
		{
			if ((typeFilter & (1 << i)) && (mem_properties.memoryTypes[i].propertyFlags & properties) == properties)
			{
				return i;
			}
		}
		LOG_ERROR("failed to find suitable memory type!");
	}
	void Buffer::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& buffer_memory)
	{
		VkBufferCreateInfo buffer_info{};
		buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		buffer_info.size = size;
		buffer_info.usage = usage;
		buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateBuffer(m_device.getHandle(), &buffer_info, nullptr, &buffer) != VK_SUCCESS)
		{
			LOG_ERROR("failed to create vertex buffer!");
		}

		VkMemoryRequirements mem_requirements;
		vkGetBufferMemoryRequirements(m_device.getHandle(), buffer, &mem_requirements);

		VkMemoryAllocateInfo alloc_info{};
		alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		alloc_info.allocationSize = mem_requirements.size;
		alloc_info.memoryTypeIndex = findMemoryType(mem_requirements.memoryTypeBits, properties);

		if (vkAllocateMemory(m_device.getHandle(), &alloc_info, nullptr, &buffer_memory) != VK_SUCCESS)
		{
			LOG_ERROR("failed to allocate vertex buffer memory!");
		}

		vkBindBufferMemory(m_device.getHandle(), buffer, buffer_memory, 0);
	}
	void Buffer::copyBuffer(VkBuffer src_buffer, VkBuffer dst_buffer, VkDeviceSize size)
	{
		std::unique_ptr<SingleTimeCommandBuffer> command_buffer = std::make_unique<SingleTimeCommandBuffer>(m_device);
		
		VkBufferCopy copyRegion{};
		copyRegion.size = size;
		vkCmdCopyBuffer(command_buffer->getHandle(), src_buffer, dst_buffer, 1, &copyRegion);
	}
}