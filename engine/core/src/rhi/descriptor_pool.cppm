#include "include/common/macro.h"
import DescriptorPool;
import DescriptorSetLayout;
import Device;

namespace ToolEngine
{
	DescriptorPool::DescriptorPool(Device& device): m_device(device)
	{
		std::array<VkDescriptorPoolSize, 2> pool_sizes {};
		// ubo
		pool_sizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		pool_sizes[0].descriptorCount = 10;
		// texture image
		pool_sizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		pool_sizes[1].descriptorCount = 10;

		VkDescriptorPoolCreateInfo pool_info{};
		pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		pool_info.poolSizeCount = static_cast<uint32_t>(pool_sizes.size());
		pool_info.pPoolSizes = pool_sizes.data();
		pool_info.maxSets = 2;

		if (vkCreateDescriptorPool(m_device.getHandle(), &pool_info, nullptr, &m_descriptor_pool) != VK_SUCCESS) 
		{
			LOG_ERROR("failed to create descriptor pool!");
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