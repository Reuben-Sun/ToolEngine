#pragma once

#include <vulkan/vulkan.h>
#include <stdexcept>
#include "device.h"
#include <optick.h>

namespace ToolEngine
{
	class CommandBuffer
	{
	public:
		CommandBuffer(Device& device);
		~CommandBuffer();

		VkCommandBuffer getHandle() const { return m_command_buffer; }
		void resetCommandBuffer();
		void submitCommandBuffer(VkSemaphore* wait_semaphores, VkSemaphore* signal_semaphores, VkFence in_flight_fence);
		void beginRecord();
		void endRecord();
		void beginRenderPass(VkRenderPassBeginInfo render_pass_info);
		void endRenderPass();
		void bindPipeline(VkPipeline pipeline);
		void setViewport(VkViewport viewport, uint32_t first_viewport_index, uint32_t viewport_count);
		void setScissor(VkRect2D scissor, uint32_t first_scissor_index, uint32_t scissor_count);
		void draw(uint32_t vertex_count, uint32_t instance_count, uint32_t first_vertex_index, uint32_t first_instance_index);
	private:
		VkCommandBuffer m_command_buffer;
		Device& m_device;
	};
}