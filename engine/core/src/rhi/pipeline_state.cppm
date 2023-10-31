#include <vulkan/vulkan.h>
#include "include/rhi/render_pass.h"

import PipelineState;
import PipelineLayout;

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
	}
}