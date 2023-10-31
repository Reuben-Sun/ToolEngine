#include <vulkan/vulkan.h>
import UniformBuffer;
import PhysicalDevice;
import Device;
import <glm/glm.hpp>;

namespace ToolEngine
{
    UniformBuffer::UniformBuffer(Device& device, PhysicalDevice& physical_device): Buffer(device, physical_device)
    {
        VkDeviceSize buffer_size = sizeof(UniformBufferObject);
        createBuffer(buffer_size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_buffer, m_memory);
        vkMapMemory(m_device.getHandle(), m_memory, 0, buffer_size, 0, &m_uniform_buffer_mapped);
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
    void UniformBuffer::updateBuffer(UniformBufferObject ubo)
    {
        memcpy(m_uniform_buffer_mapped, &ubo, sizeof(ubo));
    }
}