#include "include/rhi/buffer.h"

namespace ToolEngine
{
	Buffer::Buffer(Device& device, PhysicalDevice& physical_device, std::vector<Vertex> vertex_buffer)
		: m_device(device), m_physical_device(physical_device)
	{
		VkDeviceSize buffer_size = sizeof(vertex_buffer[0]) * vertex_buffer.size();
		// create staging buffer
		VkBuffer staging_buffer;	
		VkDeviceMemory staging_buffer_memory;
		// create source buffer for memory transfer
		createBuffer(buffer_size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, staging_buffer, staging_buffer_memory);
		void* data;
		vkMapMemory(m_device.getHandle(), staging_buffer_memory, 0, buffer_size, 0, &data);
		memcpy(data, vertex_buffer.data(), (size_t)buffer_size);
		vkUnmapMemory(m_device.getHandle(), staging_buffer_memory);
		// create destination buffer for memory transfer
		createBuffer(buffer_size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_buffer, m_memory);
		copyBuffer(staging_buffer, m_buffer, buffer_size);
		// destroy staging buffer
		vkDestroyBuffer(m_device.getHandle(), staging_buffer, nullptr);
		vkFreeMemory(m_device.getHandle(), staging_buffer_memory, nullptr);
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
	void Buffer::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& buffer_memory)
	{
		VkBufferCreateInfo buffer_info{};
		buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		buffer_info.size = size;
		buffer_info.usage = usage;
		buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateBuffer(m_device.getHandle(), &buffer_info, nullptr, &buffer) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create vertex buffer!");
		}

		VkMemoryRequirements mem_requirements;
		vkGetBufferMemoryRequirements(m_device.getHandle(), buffer, &mem_requirements);

		VkMemoryAllocateInfo alloc_info{};
		alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		alloc_info.allocationSize = mem_requirements.size;
		alloc_info.memoryTypeIndex = findMemoryType(mem_requirements.memoryTypeBits, properties);

		if (vkAllocateMemory(m_device.getHandle(), &alloc_info, nullptr, &buffer_memory) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to allocate vertex buffer memory!");
		}

		vkBindBufferMemory(m_device.getHandle(), buffer, buffer_memory, 0);
	}
	void Buffer::copyBuffer(VkBuffer src_buffer, VkBuffer dst_buffer, VkDeviceSize size)
	{
		VkCommandBufferAllocateInfo alloc_info{};
		alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		alloc_info.commandPool = m_device.getCommandPool().getHandle();
		alloc_info.commandBufferCount = 1;

		VkCommandBuffer commandBuffer;
		vkAllocateCommandBuffers(m_device.getHandle(), &alloc_info, &commandBuffer);
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		vkBeginCommandBuffer(commandBuffer, &beginInfo);

		VkBufferCopy copyRegion{};
		copyRegion.size = size;
		vkCmdCopyBuffer(commandBuffer, src_buffer, dst_buffer, 1, &copyRegion);

		vkEndCommandBuffer(commandBuffer);

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;

		vkQueueSubmit(m_device.getGraphicsQueue().getHandle(), 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(m_device.getGraphicsQueue().getHandle());

		vkFreeCommandBuffers(m_device.getHandle(), m_device.getCommandPool().getHandle(), 1, &commandBuffer);
	}
}