#pragma once

#include <memory>
#include <vulkan/vulkan.h>
#include <array>
#include "graphics_pipeline.h"
#include "include/render/pass/forward_pass.h"
#include "include/rhi/device.h"
#include "include/rhi/pipeline_state.h"
#include "include/rhi/render_pass.h"
#include "include/rhi/pipeline_layout.h"
#include "include/rhi/vertex.h"
#include "include/rhi/index.h"
#include "include/rhi/descriptor_set_layout.h"
#include "include/rhi/descriptor_pool.h"
#include "include/rhi/descriptor_sets.h"
#include "include/rhi/command_buffer.h"
#include "include/rhi/frame_buffer.h"
#include "include/rhi/vertex_buffer.h"
#include "include/rhi/index_buffer.h"
#include "include/rhi/swapchain.h"
#include "include/rhi/texture_image.h"
#include "include/rhi/image_view.h"
#include "include/rhi/sampler.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "include/render/model/model.h"
#include "include/render/scene/render_scene.h"

import Timer;

namespace ToolEngine
{
	class BlitPipeline
	{
	public:
		BlitPipeline(Device& device, PhysicalDevice& physical_device, SwapChain& swap_chain, uint32_t frames_in_flight_count);
		~BlitPipeline();
		RenderPass& getRenderPass() { return *m_forward_pass; }
		GraphicsPipeline& getPipeline() { return *m_pipeline; }
		void renderTick(CommandBuffer& command_buffer, FrameBuffer& frame_buffer, uint32_t frame_index, RenderScene& render_scene);
	private:
		Device& m_device;

		uint32_t m_frames_in_flight_count;
		std::unique_ptr<GraphicsPipeline> m_pipeline;
		std::unique_ptr<PipelineState> m_state;
		std::unique_ptr<ForwardPass> m_forward_pass;
		std::unique_ptr<PipelineLayout> m_pipeline_layout;
		std::unique_ptr<DescriptorSetLayout> m_descriptor_set_layout;
		std::unique_ptr<DescriptorSets> m_descriptor_sets;
		std::unique_ptr<DescriptorPool> m_descriptor_pool;
		std::unique_ptr<VertexBuffer> m_vertex_buffer;
		std::unique_ptr<IndexBuffer> m_index_buffer;
		std::vector<std::unique_ptr<UniformBuffer>> m_uniform_buffers;
		std::unique_ptr<TextureImage> m_texture_image;
		std::unique_ptr<ImageView> m_texture_image_view;
		std::unique_ptr<Sampler> m_texture_sampler;

		PhysicalDevice& m_physical_device;
		SwapChain& m_swap_chain;

		void createPipeline();
		void updateUniformBuffer(uint32_t current_image, RenderScene& render_scene);
	};
}