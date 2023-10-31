#include <vulkan/vulkan.h>

export module PipelineState;

import PipelineLayout;
import RenderPass;

namespace ToolEngine
{
	export struct PipelineState
	{
	public:
		void reset();
		VkPipelineShaderStageCreateInfo m_vertex_shader_stage{};
		VkPipelineShaderStageCreateInfo m_fragment_shader_stage{};
		VkPipelineLayout m_pipeline_layout{};	// pipeline layout
		VkRenderPass m_render_pass{};	// render pass
		// constant state
		VkPipelineVertexInputStateCreateInfo m_vertex_input_state{};	 // vertex input state
		VkPipelineInputAssemblyStateCreateInfo m_input_assembly_state{};	// input assembly state
		// tessellation state
		VkPipelineViewportStateCreateInfo m_viewport_state{};	// view port state
		VkPipelineRasterizationStateCreateInfo m_rasterization_state{};	// rasterization state
		VkPipelineMultisampleStateCreateInfo m_multisample_state{};	// multisample state
		VkPipelineDepthStencilStateCreateInfo m_depth_stencil_state{};	// depth stencil state	
		VkPipelineColorBlendStateCreateInfo m_color_blend_state{};	// color blend state
		VkPipelineDynamicStateCreateInfo m_dynamic_state{};	// dynamic state
		uint32_t m_subpass_index{ 0 };	// subpass index
	};
}