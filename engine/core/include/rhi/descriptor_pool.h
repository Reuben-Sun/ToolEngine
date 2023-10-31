#pragma once

#include <array>
#include <vector>
#include <vulkan/vulkan.h>
#include "device.h"
#include "descriptor_set_layout.h"

import UniformBuffer;

namespace ToolEngine
{
	class DescriptorPool
	{
	public:
		DescriptorPool(Device& device, uint32_t max_frames_in_flight_count);
		~DescriptorPool();

		VkDescriptorPool getHandle() const { return m_descriptor_pool; }
	private:
		VkDescriptorPool m_descriptor_pool;
		Device& m_device;
		uint32_t m_max_frames_in_flight_count;
	};
}