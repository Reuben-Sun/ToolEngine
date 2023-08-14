#include "include/rhi/pipeline_layout.h"

namespace ToolEngine
{
	PipelineLayout::PipelineLayout(Device& device): m_deivce(device)
	{
		VkPipelineLayoutCreateInfo pipeline_layout_info{};
		pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipeline_layout_info.setLayoutCount = 0;
		pipeline_layout_info.pushConstantRangeCount = 0;

		if (vkCreatePipelineLayout(m_deivce.getHandle(), &pipeline_layout_info, nullptr, &m_pipeline_layout) != VK_SUCCESS) 
		{
			throw std::runtime_error("failed to create pipeline layout!");
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