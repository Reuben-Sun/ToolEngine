#include "include/rhi/descriptor_pool.h"

namespace ToolEngine
{
	DescriptorPool::DescriptorPool(Device& device, uint32_t max_frames_in_flight_count)
		: m_device(device), m_max_frames_in_flight_count(max_frames_in_flight_count)
	{
		std::array<VkDescriptorPoolSize, 2> pool_sizes {};
		// ubo
		pool_sizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		pool_sizes[0].descriptorCount = m_max_frames_in_flight_count;
		// texture image
		pool_sizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		pool_sizes[1].descriptorCount = m_max_frames_in_flight_count;

		VkDescriptorPoolCreateInfo pool_info{};
		pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		pool_info.poolSizeCount = static_cast<uint32_t>(pool_sizes.size());
		pool_info.pPoolSizes = pool_sizes.data();
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