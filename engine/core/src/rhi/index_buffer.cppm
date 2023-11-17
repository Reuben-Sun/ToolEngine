#include "include/common/macro.h"
import IndexBuffer;
import Buffer;
import PhysicalDevice;
import Index;
import Device;
import BufferUtils;


namespace ToolEngine
{
	IndexBuffer::IndexBuffer(Device& device, PhysicalDevice& physical_device, std::vector<Index> index_buffer): Buffer(device, physical_device)
	{
		VkDeviceSize buffer_size = sizeof(index_buffer[0]) * index_buffer.size();

		VkBuffer staging_buffer;
		VkDeviceMemory staging_buffer_memory;

		BufferUtils::createBuffer(device, physical_device, buffer_size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, staging_buffer, staging_buffer_memory);
		vkMapMemory(device.getHandle(), staging_buffer_memory, 0, buffer_size, 0, &m_index_buffer_mapped);
		memcpy(m_index_buffer_mapped, index_buffer.data(), (size_t)buffer_size);
		vkUnmapMemory(device.getHandle(), staging_buffer_memory);

		BufferUtils::createBuffer(device, physical_device, buffer_size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_buffer, m_memory);

		BufferUtils::copyBuffer(device, staging_buffer, m_buffer, buffer_size);

		vkDestroyBuffer(device.getHandle(), staging_buffer, nullptr);
		vkFreeMemory(device.getHandle(), staging_buffer_memory, nullptr);
	}
	IndexBuffer::~IndexBuffer()
	{
		if (m_buffer != VK_NULL_HANDLE)
		{
			vkDestroyBuffer(m_device.getHandle(), m_buffer, nullptr);
		}
		if(m_memory != VK_NULL_HANDLE)
		{
			vkFreeMemory(m_device.getHandle(), m_memory, nullptr);
		}


	}
	void IndexBuffer::updateBuffer(std::vector<Index> index_buffer)
	{
		VkDeviceSize buffer_size = sizeof(index_buffer[0]) * index_buffer.size();
		memcpy(m_index_buffer_mapped, index_buffer.data(), (size_t)buffer_size);
	}
}