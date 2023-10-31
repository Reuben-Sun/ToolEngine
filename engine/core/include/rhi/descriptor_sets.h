#pragma once

#include <vector>
#include <vulkan/vulkan.h>
#include "descriptor_set_layout.h"
#include "device.h"

import DescriptorPool;

namespace ToolEngine
{
	class DescriptorSets
	{
	public:
		DescriptorSets(Device& device, DescriptorSetLayout& descriptor_set_layout, DescriptorPool& descriptor_pool, uint32_t frames_in_flight_count);
		~DescriptorSets();
		void updateDescriptorSets(VkBuffer ubo_buffer, VkImageView texture_image_view, VkSampler texture_sampler, uint32_t frames_in_flight_index);
		VkDescriptorSet* getHandlePtr(uint32_t frames_index) { return &m_descriptor_sets[frames_index]; }
	private:
		std::vector<VkDescriptorSet> m_descriptor_sets;
		Device& m_device;
		DescriptorSetLayout& m_descriptor_set_layout;
		DescriptorPool& m_descriptor_pool;
		uint32_t m_frames_in_flight_count;
	};
}