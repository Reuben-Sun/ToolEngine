#pragma once

#include <vector>
#include <vulkan/vulkan.h>
#include "device.h"
#include "uniform_buffer.h"
#include "descriptor_set_layout.h"

namespace ToolEngine
{
	class DescriptorPool
	{
	public:
		DescriptorPool();
		~DescriptorPool();
	private:
		VkDescriptorPool m_descriptor_pool;
		Device& m_device;
		//std::vector<D> m_descriptor_sets;
	};
}