#include <memory>
#include <vulkan/vulkan.h>
#include <array>
#include "include/rhi/device.h"
#include "include/rhi/physical_device.h"
#include "include/rhi/sampler.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

export module BlitPipeline;

import Timer;
import Model;
import Index;
import Vertex;
import ForwardPass;
import GraphicsPipeline;
import RenderScene;
import IndexBuffer;
import VertexBuffer;
import CommandBuffer;
import UniformBuffer;
import DescriptorPool;
import DescriptorSetLayout;
import DescriptorSets;
import FrameBuffer;
import ImageView;
import TextureImage;
import SwapChain;
import PipelineLayout;
import PipelineState;
import RenderPass;

namespace ToolEngine
{
	export class BlitPipeline
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
		PipelineState m_state;
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