#include <vulkan/vulkan.h>
#include "render_pass.h"

export module PipelineState;

import PipelineLayout;

namespace ToolEngine
{
	export class PipelineState
	{
	public:
		void reset();
		bool isDirty() const { return dirty; }
		void clearDirty();

		void setVertexShaderStage(const VkPipelineShaderStageCreateInfo& vertex_shader_stage);
		VkPipelineShaderStageCreateInfo getVertexShaderStage() const { return m_vertex_shader_stage; }
		void setFragmentShaderStage(const VkPipelineShaderStageCreateInfo& fragment_shader_stage);
		VkPipelineShaderStageCreateInfo getFragmentShaderStage() const { return m_fragment_shader_stage; }
		void setPipelineLayout(PipelineLayout& pipeline_layout);
		PipelineLayout* getPipelineLayout() const { return m_pipeline_layout; }
		void setRenderPass(const RenderPass& render_pass);
		const RenderPass* getRenderPass() const { return m_render_pass; }
		void setVertexInputState(const VkPipelineVertexInputStateCreateInfo& vertex_input_state);
		const VkPipelineVertexInputStateCreateInfo* getVertexInputState() const { return &m_vertex_input_state; }
		void setInputAssemblyState(const VkPipelineInputAssemblyStateCreateInfo& input_assembly_state);
		const VkPipelineInputAssemblyStateCreateInfo* getInputAssemblyState() const { return &m_input_assembly_state; }
		void setViewportState(const VkPipelineViewportStateCreateInfo& viewport_state);
		const VkPipelineViewportStateCreateInfo* getViewportState() const { return &m_viewport_state; }
		void setRasterizationState(const VkPipelineRasterizationStateCreateInfo& rasterization_state);
		const VkPipelineRasterizationStateCreateInfo* getRasterizationState() const { return &m_rasterization_state; }
		void setMultisampleState(const VkPipelineMultisampleStateCreateInfo& multisample_state);
		const VkPipelineMultisampleStateCreateInfo* getMultisampleState() const { return &m_multisample_state; }
		void setColorBlendState(const VkPipelineColorBlendStateCreateInfo& color_blend_state);
		const VkPipelineDepthStencilStateCreateInfo* getDepthStencilState() const { return &m_depth_stencil_state; }
		void setDepthStencilState(const VkPipelineDepthStencilStateCreateInfo& depth_stencil_state);
		const VkPipelineColorBlendStateCreateInfo* getColorBlendState() const { return &m_color_blend_state; }
		void setDynamicState(const VkPipelineDynamicStateCreateInfo& dynamic_state);
		const VkPipelineDynamicStateCreateInfo* getDynamicState() const { return &m_dynamic_state; }
		void setSubpassIndex(uint32_t subpass_index);
		uint32_t getSubpassIndex() const { return m_subpass_index; }

	private:
		bool dirty{ false };
		VkPipelineShaderStageCreateInfo m_vertex_shader_stage{};
		VkPipelineShaderStageCreateInfo m_fragment_shader_stage{};
		PipelineLayout* m_pipeline_layout{ nullptr };	// pipeline layout
		const RenderPass* m_render_pass{ nullptr };	// render pass
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