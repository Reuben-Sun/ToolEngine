#include <vulkan/vulkan.h>

import Pipeline;
import PipelineState;
import Device;

namespace ToolEngine
{
	Pipeline::Pipeline(Device& device): m_device(device)
	{
	}

	Pipeline::~Pipeline()
	{
		if (m_pipeline != VK_NULL_HANDLE)
		{
			vkDestroyPipeline(m_device.getHandle(), m_pipeline, nullptr);
		}
	}
}