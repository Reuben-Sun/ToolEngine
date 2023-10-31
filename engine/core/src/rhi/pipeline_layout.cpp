#include "include/rhi/pipeline_layout.h"
#include "include/common/macro.h"

namespace ToolEngine
{
	PipelineLayout::PipelineLayout(Device& device, const VkPipelineLayoutCreateInfo& create_info): m_deivce(device)
	{
		if (vkCreatePipelineLayout(m_deivce.getHandle(), &create_info, nullptr, &m_pipeline_layout) != VK_SUCCESS)
		{
			LOG_ERROR("failed to create pipeline layout!");
		}
	}
	
	PipelineLayout::~PipelineLayout()
	{
		if (m_pipeline_layout != VK_NULL_HANDLE)
		{
			vkDestroyPipelineLayout(m_deivce.getHandle(), m_pipeline_layout, nullptr);
		}
	}
}