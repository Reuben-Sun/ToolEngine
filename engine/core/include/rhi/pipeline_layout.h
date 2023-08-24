#pragma once

#include <vulkan/vulkan.h>
#include "device.h"

namespace ToolEngine
{
	class PipelineLayout
	{
	public:
		PipelineLayout(Device& device, const VkPipelineLayoutCreateInfo& create_info);
		~PipelineLayout();

		VkPipelineLayout getHandle() const { return m_pipeline_layout; }

	private:
		VkPipelineLayout m_pipeline_layout;
		Device& m_deivce;
	};
}