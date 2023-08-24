#pragma once

#include <vulkan/vulkan.h>
#include "device.h"
#include "pipeline_layout.h"

namespace ToolEngine
{
	class DescriptorSetLayout
	{
	public:
		DescriptorSetLayout(Device& device, PipelineLayout& pipeline_layout);
		~DescriptorSetLayout();

		VkDescriptorSetLayout getHandle() const { return m_descriptor_set_layout; }
	private:
		VkDescriptorSetLayout m_descriptor_set_layout{ VK_NULL_HANDLE };
		Device& m_device;
		PipelineLayout& m_pipeline_layout;
	};
}