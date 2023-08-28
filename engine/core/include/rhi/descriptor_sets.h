#pragma once

#include <vector>
#include <vulkan/vulkan.h>
#include "descriptor_set_layout.h"
#include "device.h"
#include "descriptor_pool.h"

namespace ToolEngine
{
	class DescriptorSets
	{
	public:
		DescriptorSets(Device& device, DescriptorSetLayout& descriptor_set_layout, DescriptorPool& descriptor_pool, uint32_t frames_in_flight_count);
		~DescriptorSets();
	private:
		std::vector<VkDescriptorSet> m_descriptor_sets;
		Device& m_device;
		DescriptorSetLayout& m_descriptor_set_layout;
		DescriptorPool& m_descriptor_pool;
		uint32_t m_frames_in_flight_count;
	};
}