#include "include/common/macro.h"
import VertexBuffer;
import Buffer;
import Vertex;
import PhysicalDevice;
import Device;
import BufferUtils;

namespace ToolEngine
{
	VertexBuffer::VertexBuffer(Device& device, PhysicalDevice& physical_device, std::vector<Vertex> vertex_buffer): Buffer(device, physical_device)
	{
		VkDeviceSize buffer_size = sizeof(vertex_buffer[0]) * vertex_buffer.size();
		// CPU is easy and quick to access memory, but it's hard to copy buffer from CPU to GPU, so we use staging buffer
		// create staging buffer in CPU memory
		VkBuffer staging_buffer;
		VkDeviceMemory staging_buffer_memory;
		BufferUtils::createBuffer(device, physical_device, buffer_size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, staging_buffer, staging_buffer_memory);
		vkMapMemory(m_device.getHandle(), staging_buffer_memory, 0, buffer_size, 0, &m_vertex_buffer_mapped);
		memcpy(m_vertex_buffer_mapped, vertex_buffer.data(), (size_t)buffer_size);
		vkUnmapMemory(m_device.getHandle(), staging_buffer_memory);
		// create destination buffer in device memory
		BufferUtils::createBuffer(device, physical_device, buffer_size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_buffer, m_memory);
		// use vulkan command to copy buffer from staging buffer to destination buffer
		BufferUtils::copyBuffer(device, staging_buffer, m_buffer, buffer_size);
		// destroy staging buffer
		vkDestroyBuffer(m_device.getHandle(), staging_buffer, nullptr);
		vkFreeMemory(m_device.getHandle(), staging_buffer_memory, nullptr);
	}

	VertexBuffer::~VertexBuffer()
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

	void VertexBuffer::updateBuffer(std::vector<Vertex> vertex_buffer)
	{
		VkDeviceSize buffer_size = sizeof(vertex_buffer[0]) * vertex_buffer.size();
		memcpy(m_vertex_buffer_mapped, vertex_buffer.data(), (size_t)buffer_size);
	}

	
}