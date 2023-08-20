#include "include/rhi/buffer.h"

namespace ToolEngine
{
	Buffer::Buffer(Device& device, PhysicalDevice& physical_device, std::vector<Vertex> vertex_buffer)
		: m_device(device), m_physical_device(physical_device)
	{
		VkBufferCreateInfo buffer_info{};
		buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		buffer_info.size = sizeof(vertex_buffer[0]) * vertex_buffer.size();
		buffer_info.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
		buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateBuffer(m_device.getHandle(), &buffer_info, nullptr, &m_buffer) != VK_SUCCESS) 
		{
			throw std::runtime_error("failed to create vertex buffer!");
		}

		VkMemoryRequirements mem_requirements;
		vkGetBufferMemoryRequirements(m_device.getHandle(), m_buffer, &mem_requirements);

		VkMemoryAllocateInfo alloc_info{};
		alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		alloc_info.allocationSize = mem_requirements.size;
		alloc_info.memoryTypeIndex = findMemoryType(mem_requirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		if (vkAllocateMemory(m_device.getHandle(), &alloc_info, nullptr, &m_memory) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate vertex buffer memory!");
		}

		vkBindBufferMemory(m_device.getHandle(), m_buffer, m_memory, 0);

		void* data;
		vkMapMemory(m_device.getHandle(), m_memory, 0, buffer_info.size, 0, &data);
		memcpy(data, vertex_buffer.data(), (size_t)buffer_info.size);
		vkUnmapMemory(m_device.getHandle(), m_memory);
	}

	Buffer::~Buffer()
	{
		if (m_buffer != VK_NULL_HANDLE)
		{
			vkDestroyBuffer(m_device.getHandle(), m_buffer, nullptr);
		}
		if (m_memory != VK_NULL_HANDLE)
		{
			vkFreeMemory(m_device.getHandle(), m_memory, nullptr);
		}
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

		throw std::runtime_error("failed to find suitable memory type!");
	}
}