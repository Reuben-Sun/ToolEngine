#include <vulkan/vulkan.h>
#include "include/common/macro.h"
import GraphicsPipeline;

namespace ToolEngine
{
	GraphicsPipeline::GraphicsPipeline(Device& device, PipelineState pipeline_state): Pipeline{device}
	{
        VkPipelineShaderStageCreateInfo shader_stages[] = { pipeline_state.m_vertex_shader_stage, pipeline_state.m_fragment_shader_stage };

        VkGraphicsPipelineCreateInfo pipeline_info{};
        pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipeline_info.stageCount = 2;
        pipeline_info.pStages = shader_stages;
        pipeline_info.pVertexInputState = &pipeline_state.m_vertex_input_state;
        pipeline_info.pInputAssemblyState = &pipeline_state.m_input_assembly_state;
        pipeline_info.pViewportState = &pipeline_state.m_viewport_state;
        pipeline_info.pRasterizationState = &pipeline_state.m_rasterization_state;
        pipeline_info.pMultisampleState = &pipeline_state.m_multisample_state;
        pipeline_info.pDepthStencilState = &pipeline_state.m_depth_stencil_state;
        pipeline_info.pColorBlendState = &pipeline_state.m_color_blend_state;
        pipeline_info.pDynamicState = &pipeline_state.m_dynamic_state;
        pipeline_info.layout = pipeline_state.m_pipeline_layout;
        pipeline_info.renderPass = pipeline_state.m_render_pass;
        pipeline_info.subpass = pipeline_state.m_subpass_index;
        pipeline_info.basePipelineHandle = VK_NULL_HANDLE;

        if (vkCreateGraphicsPipelines(m_device.getHandle(), VK_NULL_HANDLE, 1, &pipeline_info, nullptr, &m_pipeline) != VK_SUCCESS)
        {
            LOG_ERROR("failed to create graphics pipeline!");
        }
	}
}