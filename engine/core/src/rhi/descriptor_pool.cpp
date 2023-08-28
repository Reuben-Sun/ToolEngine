#include "include/rhi/descriptor_pool.h"

namespace ToolEngine
{
	DescriptorPool::DescriptorPool(Device& device, uint32_t max_frames_in_flight_count)
		: m_device(device), m_max_frames_in_flight_count(max_frames_in_flight_count)
	{
		VkDescriptorPoolSize pool_size{};
		pool_size.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		pool_size.descriptorCount = m_max_frames_in_flight_count;

		VkDescriptorPoolCreateInfo pool_info{};
		pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		pool_info.poolSizeCount = 1;
		pool_info.pPoolSizes = &pool_size;
		pool_info.maxSets = m_max_frames_in_flight_count;

		if (vkCreateDescriptorPool(m_device.getHandle(), &pool_info, nullptr, &m_descriptor_pool) != VK_SUCCESS) 
		{
			throw std::runtime_error("failed to create descriptor pool!");
		}
	}

	DescriptorPool::~DescriptorPool()
	{
		if (m_descriptor_pool != VK_NULL_HANDLE)
		{
			vkDestroyDescriptorPool(m_device.getHandle(), m_descriptor_pool, nullptr);
		}
	}
}