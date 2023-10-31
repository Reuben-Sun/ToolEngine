#include <vulkan/vulkan.h>
#include "device.h"

export module DescriptorPool;

import UniformBuffer;
import DescriptorSetLayout;

namespace ToolEngine
{
	export class DescriptorPool
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