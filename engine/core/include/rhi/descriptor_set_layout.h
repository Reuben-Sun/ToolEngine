#pragma once

#include <array>
#include <vulkan/vulkan.h>
#include "device.h"
#include "pipeline_layout.h"

namespace ToolEngine
{
	class DescriptorSetLayout
	{
	public:
		DescriptorSetLayout(Device& device);
		~DescriptorSetLayout();

		VkDescriptorSetLayout getHandle() const { return m_descriptor_set_layout; }
		const VkDescriptorSetLayout* getHandlePtr() { return &m_descriptor_set_layout; }
	private:
		VkDescriptorSetLayout m_descriptor_set_layout{ VK_NULL_HANDLE };
		Device& m_device;
	};
}