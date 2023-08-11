#pragma once

#include <vulkan/vulkan.h>
#include "pipeline_layout.h"
#include "render_pass.h"

namespace ToolEngine
{
	class PipelineState
	{
	public:
		void reset();
		bool isDirty() const { return dirty; }
		void clearDirty();

		void setPipelineLayout(PipelineLayout& pipeline_layout);
		PipelineLayout* getPipelineLayout() const { return m_pipeline_layout; }
		void setRenderPass(const RenderPass& render_pass);
		const RenderPass* getRenderPass() const { return m_render_pass; }
		void setVertexInputState(const VkPipelineVertexInputStateCreateInfo& vertex_input_state);
		VkPipelineVertexInputStateCreateInfo getVertexInputState() const { return m_vertex_input_state; }
		void setInputAssemblyState(const VkPipelineInputAssemblyStateCreateInfo& input_assembly_state);
		VkPipelineInputAssemblyStateCreateInfo getInputAssemblyState() const { return m_input_assembly_state; }
		void setViewportState(const VkPipelineViewportStateCreateInfo& viewport_state);
		VkPipelineViewportStateCreateInfo getViewportState() const { return m_viewport_state; }
		void setRasterizationState(const VkPipelineRasterizationStateCreateInfo& rasterization_state);
		VkPipelineRasterizationStateCreateInfo getRasterizationState() const { return m_rasterization_state; }
		void setMultisampleState(const VkPipelineMultisampleStateCreateInfo& multisample_state);
		VkPipelineMultisampleStateCreateInfo getMultisampleState() const { return m_multisample_state; }
		void setColorBlendState(const VkPipelineColorBlendStateCreateInfo& color_blend_state);
		VkPipelineColorBlendStateCreateInfo getColorBlendState() const { return m_color_blend_state; }
		void setDynamicState(const VkPipelineDynamicStateCreateInfo& dynamic_state);
		VkPipelineDynamicStateCreateInfo getDynamicState() const { return m_dynamic_state; }
		void setSubpassIndex(uint32_t subpass_index);
		uint32_t getSubpassIndex() const { return m_subpass_index; }

	private:
		bool dirty{ false };
		PipelineLayout* m_pipeline_layout{ nullptr };	// pipeline layout
		const RenderPass* m_render_pass{ nullptr };	// render pass
		// constant state
		VkPipelineVertexInputStateCreateInfo m_vertex_input_state{};	 // vertex input state
		VkPipelineInputAssemblyStateCreateInfo m_input_assembly_state{};	// input assembly state
		// tessellation state
		VkPipelineViewportStateCreateInfo m_viewport_state{};	// view port state
		VkPipelineRasterizationStateCreateInfo m_rasterization_state{};	// rasterization state
		VkPipelineMultisampleStateCreateInfo m_multisample_state{};	// multisample state
		// depth stencil state	
		VkPipelineColorBlendStateCreateInfo m_color_blend_state{};	// color blend state
		VkPipelineDynamicStateCreateInfo m_dynamic_state{};	// dynamic state
		uint32_t m_subpass_index{ 0 };	// subpass index
	};
}