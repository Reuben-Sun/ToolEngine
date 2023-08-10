#pragma once

#include <vulkan/vulkan.h>
#include "include/rhi/pipeline_layout.h"
#include "include/rhi/render_pass.h"

namespace ToolEngine
{
	class PipelineState
	{
	public:
		void reset();
		bool isDirty() const { return dirty; }
		void clearDirty();
		void setPipelineLayout(PipelineLayout& pipeline_layout);
		void setRenderPass(const RenderPass& render_pass);

	private:
		// dirty
		bool dirty{ false };
		// layout
		PipelineLayout* m_pipeline_layout{ nullptr };
		// render pass
		const RenderPass* m_render_pass{ nullptr };
		// constant state
		// vertex input state
		// input assembly state
		// tessellation state
		// input assembly state
		// view port state
		// rasterization state
		// multisample state
		// depth stencil state
		// color blend state
		// subpass index
	};
}