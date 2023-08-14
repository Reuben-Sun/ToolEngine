#include "include/render/graphics_pipeline.h"

namespace ToolEngine
{
	GraphicsPipeline::GraphicsPipeline(Device& device, PipelineState& pipeline_state): Pipeline{device}
	{
        // shader
		ShaderModule vertex_shader_module{device, "Debug/shaders/vert.spv"};
		ShaderModule fragment_shader_module{device, "Debug/shaders/frag.spv"};

        VkPipelineShaderStageCreateInfo vert_shader_stage_info{};
        vert_shader_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vert_shader_stage_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
        vert_shader_stage_info.module = vertex_shader_module.getHandle();
        vert_shader_stage_info.pName = "main";
        VkPipelineShaderStageCreateInfo frag_shader_stage_info{};
        frag_shader_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        frag_shader_stage_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        frag_shader_stage_info.module = fragment_shader_module.getHandle();
        frag_shader_stage_info.pName = "main";
        VkPipelineShaderStageCreateInfo shader_stages[] = { vert_shader_stage_info, frag_shader_stage_info };

        VkGraphicsPipelineCreateInfo pipelineInfo{};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineInfo.stageCount = 2;
        pipelineInfo.pStages = shader_stages;
        pipelineInfo.pVertexInputState = &pipeline_state.getVertexInputState();
        pipelineInfo.pInputAssemblyState = &pipeline_state.getInputAssemblyState();
        pipelineInfo.pViewportState = &pipeline_state.getViewportState();
        pipelineInfo.pRasterizationState = &pipeline_state.getRasterizationState();
        pipelineInfo.pMultisampleState = &pipeline_state.getMultisampleState();
        pipelineInfo.pColorBlendState = &pipeline_state.getColorBlendState();
        pipelineInfo.pDynamicState = &pipeline_state.getDynamicState();
        pipelineInfo.layout = pipeline_state.getPipelineLayout()->getHandle();
        pipelineInfo.renderPass = pipeline_state.getRenderPass()->getHandle();
        pipelineInfo.subpass = 0;
        pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

        if (vkCreateGraphicsPipelines(device.getHandle(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_pipeline) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create graphics pipeline!");
        }
	}
}