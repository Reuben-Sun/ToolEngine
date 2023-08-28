#pragma once

#include <memory>
#include <vulkan/vulkan.h>
#include "graphics_pipeline.h"
#include "include/rhi/device.h"
#include "include/rhi/pipeline_state.h"
#include "include/rhi/render_pass.h"
#include "include/rhi/pipeline_layout.h"
#include "include/rhi/vertex_descriptor.h"
#include "include/rhi/descriptor_set_layout.h"
#include "include/rhi/descriptor_pool.h"

namespace ToolEngine
{
	class BlitPipeline
	{
	public:
		BlitPipeline(Device& device, VkFormat format, uint32_t frames_in_flight_count);
		~BlitPipeline();
		RenderPass& getRenderPass() { return *m_render_pass; }
		GraphicsPipeline& getPipeline() { return *m_pipeline; }
	private:
		Device& m_device;

		VkFormat m_format;
		uint32_t m_frames_in_flight_count;
		std::unique_ptr<GraphicsPipeline> m_pipeline;
		std::unique_ptr<PipelineState> m_state;
		std::unique_ptr<RenderPass> m_render_pass;
		std::unique_ptr<PipelineLayout> m_pipeline_layout;
		std::unique_ptr<DescriptorSetLayout> m_descriptor_set_layout;
		std::unique_ptr<DescriptorPool> m_descriptor_pool;

		void createPipeline();
	};
}