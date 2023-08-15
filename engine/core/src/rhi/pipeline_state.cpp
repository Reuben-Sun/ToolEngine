#include "include/rhi/pipeline_state.h"

namespace ToolEngine
{
	void PipelineState::reset()
	{
		m_vertex_shader_stage = {};
		m_fragment_shader_stage = {};
		m_pipeline_layout = nullptr;
		m_render_pass = nullptr;
		m_vertex_input_state = {};
		m_input_assembly_state = {};
		m_viewport_state = {};
		m_rasterization_state = {};
		m_multisample_state = {};
		m_color_blend_state = {};
		m_dynamic_state = {};
		m_subpass_index = 0;
		dirty = false;
	}

	void PipelineState::clearDirty()
	{
		dirty = false;
	}

	void PipelineState::setVertexShaderStage(const VkPipelineShaderStageCreateInfo& vertex_shader_stage)
	{
		m_vertex_shader_stage = vertex_shader_stage;
		dirty = true;
	}

	void PipelineState::setFragmentShaderStage(const VkPipelineShaderStageCreateInfo& fragment_shader_stage)
	{
		m_fragment_shader_stage = fragment_shader_stage;
		dirty = true;
	}

	void PipelineState::setPipelineLayout(PipelineLayout& pipeline_layout)
	{
		if (m_pipeline_layout != VK_NULL_HANDLE) 
		{
			if (pipeline_layout.getHandle() != m_pipeline_layout->getHandle())
			{
				m_pipeline_layout = &pipeline_layout;
				dirty = true;
			}
		}
		else
		{
			m_pipeline_layout = &pipeline_layout;
			dirty = true;
		}
	}

	void PipelineState::setRenderPass(const RenderPass& render_pass)
	{
		if (m_render_pass != VK_NULL_HANDLE)
		{
			if (render_pass.getHandle() != m_render_pass->getHandle())
			{
				m_render_pass = &render_pass;
				dirty = true;
			}
		}
		else
		{
			m_render_pass = &render_pass;
			dirty = true;
		}
	}
	void PipelineState::setVertexInputState(const VkPipelineVertexInputStateCreateInfo& vertex_input_state)
	{
		m_vertex_input_state = vertex_input_state;
		dirty = true;
	}
	void PipelineState::setInputAssemblyState(const VkPipelineInputAssemblyStateCreateInfo& input_assembly_state)
	{
		m_input_assembly_state = input_assembly_state;
		dirty = true;
	}
	void PipelineState::setViewportState(const VkPipelineViewportStateCreateInfo& viewport_state)
	{
		m_viewport_state = viewport_state;
		dirty = true;
	}
	void PipelineState::setRasterizationState(const VkPipelineRasterizationStateCreateInfo& rasterization_state)
	{
		m_rasterization_state = rasterization_state;
		dirty = true;
	}
	void PipelineState::setMultisampleState(const VkPipelineMultisampleStateCreateInfo& multisample_state)
	{
		m_multisample_state = multisample_state;
		dirty = true;
	}
	void PipelineState::setColorBlendState(const VkPipelineColorBlendStateCreateInfo& color_blend_state)
	{
		m_color_blend_state = color_blend_state;
		dirty = true;
	}
	void PipelineState::setDynamicState(const VkPipelineDynamicStateCreateInfo& dynamic_state)
	{
		m_dynamic_state = dynamic_state;
		dirty = true;
	}
	void PipelineState::setSubpassIndex(uint32_t subpass_index)
	{
		if (m_subpass_index != subpass_index)
		{
			m_subpass_index = subpass_index;
			dirty = true;
		}
	}
}