#pragma once

#include <memory>
#include <vulkan/vulkan.h>
#include "graphics_pipeline.h"
#include "include/rhi/device.h"
#include "include/rhi/pipeline_state.h"
#include "include/rhi/render_pass.h"
#include "include/rhi/pipeline_layout.h"

namespace ToolEngine
{
	class BlitPipeline
	{
	public:
		BlitPipeline(Device& device, VkFormat format);
		~BlitPipeline();
		RenderPass& getRenderPass() { return *m_render_pass; }
	private:
		Device& m_device;

		std::unique_ptr<GraphicsPipeline> m_pipeline;
		std::unique_ptr<PipelineState> m_state;
		std::unique_ptr<RenderPass> m_render_pass;
		std::unique_ptr<PipelineLayout> m_pipeline_layout;
	};
}