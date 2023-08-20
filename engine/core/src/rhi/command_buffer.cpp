#include "include/rhi/command_buffer.h"

namespace ToolEngine
{
	CommandBuffer::CommandBuffer(Device& device, uint32_t buffer_count): m_device(device), m_buffer_count(buffer_count)
	{
		VkCommandBufferAllocateInfo alloc_info{};
		alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		alloc_info.commandPool = m_device.getCommandPool().getHandle();
		alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		alloc_info.commandBufferCount = m_buffer_count;

		m_command_buffers.resize(m_buffer_count);
		if (vkAllocateCommandBuffers(m_device.getHandle(), &alloc_info, m_command_buffers.data()) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to allocate command buffers!");
		}
	}
	CommandBuffer::~CommandBuffer()
	{
	}
	void CommandBuffer::resetCommandBuffer(uint32_t current_frame)
	{
		OPTICK_EVENT();
		vkResetCommandBuffer(m_command_buffers[current_frame], 0);
	}
	void CommandBuffer::submitCommandBuffer(uint32_t current_frame, VkSemaphore* wait_semaphores, VkSemaphore* signal_semaphores, VkFence in_flight_fence)
	{
		OPTICK_EVENT();
		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = wait_semaphores;
		submitInfo.pWaitDstStageMask = waitStages;

		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &m_command_buffers[current_frame];

		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signal_semaphores;

		if (vkQueueSubmit(m_device.getGraphicsQueue().getHandle(), 1, &submitInfo, in_flight_fence) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to submit draw command buffer!");
		}
	}
	void CommandBuffer::beginRecord(uint32_t current_frame)
	{
		OPTICK_EVENT();
		VkCommandBufferBeginInfo begin_info{};
		begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		if (vkBeginCommandBuffer(m_command_buffers[current_frame], &begin_info) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to begin recording command buffer!");
		}
	}
	void CommandBuffer::endRecord(uint32_t current_frame)
	{
		OPTICK_EVENT();
		if (vkEndCommandBuffer(m_command_buffers[current_frame]) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to record command buffer!");
		}
	}
	void CommandBuffer::beginRenderPass(uint32_t current_frame, VkRenderPassBeginInfo render_pass_info)
	{
		OPTICK_EVENT();
		vkCmdBeginRenderPass(m_command_buffers[current_frame], &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);
	}
	void CommandBuffer::endRenderPass(uint32_t current_frame)
	{
		OPTICK_EVENT();
		vkCmdEndRenderPass(m_command_buffers[current_frame]);
	}
	void CommandBuffer::bindPipeline(uint32_t current_frame, VkPipeline pipeline)
	{
		OPTICK_EVENT();
		vkCmdBindPipeline(m_command_buffers[current_frame], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
	}
	void CommandBuffer::setViewport(uint32_t current_frame, VkViewport viewport, uint32_t first_viewport_index, uint32_t viewport_count)
	{
		OPTICK_EVENT();
		vkCmdSetViewport(m_command_buffers[current_frame], first_viewport_index, viewport_count, &viewport);
	}
	void CommandBuffer::setScissor(uint32_t current_frame, VkRect2D scissor, uint32_t first_scissor_index, uint32_t scissor_count)
	{
		OPTICK_EVENT();
		vkCmdSetScissor(m_command_buffers[current_frame], first_scissor_index, scissor_count, &scissor);
	}
	void CommandBuffer::draw(uint32_t current_frame, uint32_t vertex_count, uint32_t instance_count, uint32_t first_vertex_index, uint32_t first_instance_index)
	{
		OPTICK_EVENT();
		vkCmdDraw(m_command_buffers[current_frame], vertex_count, instance_count, first_vertex_index, first_instance_index);
	}
}