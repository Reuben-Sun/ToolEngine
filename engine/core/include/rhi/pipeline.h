#pragma once

#include <vulkan/vulkan.h>
#include "device.h"

import PipelineState;

namespace ToolEngine
{
	class Pipeline
	{
	public:
		Pipeline(Device& device);
		virtual ~Pipeline();

		VkPipeline getHandle() const { return m_pipeline; }
		const PipelineState& getPipelineState() const { return m_pipeline_state; }

	protected:
		VkPipeline m_pipeline{ VK_NULL_HANDLE };
		Device& m_device;
		PipelineState m_pipeline_state;
	};
}