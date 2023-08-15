#include "include/render/graphics_pipeline.h"

namespace ToolEngine
{
	GraphicsPipeline::GraphicsPipeline(Device& device, PipelineState& pipeline_state): Pipeline{device}
	{
        VkPipelineShaderStageCreateInfo shader_stages[] = { pipeline_state.getVertexShaderStage(), pipeline_state.getFragmentShaderStage() };

        VkGraphicsPipelineCreateInfo pipeline_info{};
        pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipeline_info.stageCount = 2;
        pipeline_info.pStages = shader_stages;
        pipeline_info.pVertexInputState = &pipeline_state.getVertexInputState();
        pipeline_info.pInputAssemblyState = &pipeline_state.getInputAssemblyState();
        pipeline_info.pViewportState = &pipeline_state.getViewportState();
        pipeline_info.pRasterizationState = &pipeline_state.getRasterizationState();
        pipeline_info.pMultisampleState = &pipeline_state.getMultisampleState();
        pipeline_info.pColorBlendState = &pipeline_state.getColorBlendState();
        pipeline_info.pDynamicState = &pipeline_state.getDynamicState();
        pipeline_info.layout = pipeline_state.getPipelineLayout()->getHandle();
        pipeline_info.renderPass = pipeline_state.getRenderPass()->getHandle();
        pipeline_info.subpass = pipeline_state.getSubpassIndex();
        pipeline_info.basePipelineHandle = VK_NULL_HANDLE;

        if (vkCreateGraphicsPipelines(m_device.getHandle(), VK_NULL_HANDLE, 1, &pipeline_info, nullptr, &m_pipeline) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create graphics pipeline!");
        }
	}
}