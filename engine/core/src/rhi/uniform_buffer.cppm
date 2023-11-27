#include "include/common/macro.h"
import UniformBuffer;
import PhysicalDevice;
import Device;
import BufferUtils;

namespace ToolEngine
{
    UniformBuffer::UniformBuffer(Device& device, PhysicalDevice& physical_device, UniformBufferType ubo_type): Buffer(device, physical_device), m_ubo_type(ubo_type)
    {
        if (m_ubo_type == UniformBufferType::Global)
        {
            m_ubo_size = sizeof(GlobalUniformBufferObject);
        }
        else if (m_ubo_type == UniformBufferType::PerMesh)
        {
            m_ubo_size = sizeof(PerMeshUniformBufferObject);
        }
        VkDeviceSize buffer_size = m_ubo_size;
        BufferUtils::createBuffer(device, physical_device, buffer_size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_buffer, m_memory);
        vkMapMemory(m_device.getHandle(), m_memory, 0, buffer_size, 0, &m_uniform_buffer_mapped);

        m_descriptor.buffer = m_buffer;
        m_descriptor.offset = 0;
        m_descriptor.range = m_ubo_size;
    }
    UniformBuffer::~UniformBuffer()
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
    void UniformBuffer::updateBuffer(const void* ubo)
    {
        memcpy(m_uniform_buffer_mapped, &ubo, m_ubo_size);
    }
    uint32_t UniformBuffer::getAlignmentSize()
    {
        if(m_ubo_type == UniformBufferType::Global)
		{
			return sizeof(GlobalUniformBufferObject);
		}
		else if(m_ubo_type == UniformBufferType::PerMesh)
		{
			return sizeof(PerMeshUniformBufferObject);
		}
    }
}