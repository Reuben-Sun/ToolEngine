#pragma once

#include <vulkan/vulkan.h>

namespace ToolEngine
{
	class DescriptorSet
	{
	public:
		DescriptorSet();
		~DescriptorSet();
	private:
		VkDescriptorSet m_descriptor_set;
	};
}