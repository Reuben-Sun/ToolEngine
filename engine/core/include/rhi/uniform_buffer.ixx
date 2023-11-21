#include "include/common/macro.h"

export module UniformBuffer;

import Buffer;
import PhysicalDevice;
import Device;
import BufferUtils;

namespace ToolEngine
{
	export struct GlobalUniformBufferObject
	{
		glm::mat4 view_matrix;
		glm::mat4 projection_matrix;
	};

	export struct PerMeshUniformBufferObject
	{
		glm::mat4 model_matrix;
	};

	export template <typename T> class UniformBuffer: public Buffer
	{
	public:
		UniformBuffer(Device& device, PhysicalDevice& physical_device, uint32_t binding_index);
		virtual ~UniformBuffer();
		void updateBuffer(const T& ubo);
		VkBuffer getHandle() const { return m_buffer; }
		VkDescriptorBufferInfo* getDescriptor()
		{
			return &m_descriptor;
		};
	private:
		VkBuffer m_buffer;
		VkDeviceMemory m_memory;
		void* m_uniform_buffer_mapped;
		VkDescriptorBufferInfo m_descriptor;
	};

	template <typename T>
	UniformBuffer<T>::UniformBuffer(Device& device, PhysicalDevice& physical_device, uint32_t binding_index) : Buffer(device, physical_device)
	{
		VkDeviceSize buffer_size = sizeof(T);
		BufferUtils::createBuffer(device, physical_device, buffer_size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_buffer, m_memory);
		vkMapMemory(m_device.getHandle(), m_memory, 0, buffer_size, 0, &m_uniform_buffer_mapped);

		m_descriptor.buffer = m_buffer;
		m_descriptor.offset = 0;
		m_descriptor.range = sizeof(T);
	}
	template <typename T>
	UniformBuffer<T>::~UniformBuffer()
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
	template <typename T>
	void UniformBuffer<T>::updateBuffer(const T& ubo)
	{
		memcpy(m_uniform_buffer_mapped, &ubo, sizeof(ubo));
	}
}