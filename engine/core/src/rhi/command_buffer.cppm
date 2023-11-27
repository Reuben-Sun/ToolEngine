#include "include/common/macro.h"
import CommandBuffer;
import Device;
import RenderPass;
import FrameBuffer;
import DebugUtils;
import VertexBuffer;
import IndexBuffer;

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
			LOG_ERROR("failed to allocate command buffers!");
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
			LOG_ERROR("failed to submit draw command buffer!");
		}
	}
	void CommandBuffer::beginRecord(uint32_t current_frame)
	{
		OPTICK_EVENT();
		VkCommandBufferBeginInfo begin_info{};
		begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		if (vkBeginCommandBuffer(m_command_buffers[current_frame], &begin_info) != VK_SUCCESS)
		{
			LOG_ERROR("failed to begin recording command buffer!");
		}
	}
	void CommandBuffer::endRecord(uint32_t current_frame)
	{
		OPTICK_EVENT();
		if (vkEndCommandBuffer(m_command_buffers[current_frame]) != VK_SUCCESS)
		{
			LOG_ERROR("failed to record command buffer!");
		}
	}
	void CommandBuffer::beginRenderPass(uint32_t current_frame, RenderPass& render_pass, FrameBuffer& frame_buffer, VkExtent2D extent)
	{
		OPTICK_EVENT();
		DebugUtils::beginDebugUtilsLabelEXT(m_command_buffers[current_frame], "forward");
		VkRenderPassBeginInfo render_pass_info{};
		render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		render_pass_info.renderPass = render_pass.getHandle();
		render_pass_info.framebuffer = frame_buffer.getHandle();
		render_pass_info.renderArea.offset = { 0, 0 };
		render_pass_info.renderArea.extent = extent;
		std::array<VkClearValue, 2> clear_colors{};
		clear_colors[0].color = { {0.0f, 0.0f, 0.0f, 1.0f} };
		clear_colors[1].depthStencil = { 1.0f, 0 };
		render_pass_info.clearValueCount = static_cast<uint32_t>(clear_colors.size());
		render_pass_info.pClearValues = clear_colors.data();
		vkCmdBeginRenderPass(m_command_buffers[current_frame], &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);
	}
	void CommandBuffer::endRenderPass(uint32_t current_frame)
	{
		OPTICK_EVENT();
		vkCmdEndRenderPass(m_command_buffers[current_frame]);
		DebugUtils::endDebugUtilsLabelEXT(m_command_buffers[current_frame]);
	}
	void CommandBuffer::bindPipeline(uint32_t current_frame, VkPipeline pipeline)
	{
		OPTICK_EVENT();
		vkCmdBindPipeline(m_command_buffers[current_frame], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
	}
	void CommandBuffer::setViewport(uint32_t current_frame, VkExtent2D extent, float min_depth, float max_depth, uint32_t first_viewport_index, uint32_t viewport_count)
	{
		OPTICK_EVENT();
		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = extent.width;
		viewport.height = extent.height;
		viewport.minDepth = min_depth;
		viewport.maxDepth = max_depth;
		vkCmdSetViewport(m_command_buffers[current_frame], first_viewport_index, viewport_count, &viewport);
	}
	void CommandBuffer::setScissor(uint32_t current_frame, VkExtent2D extent, uint32_t first_scissor_index, uint32_t scissor_count)
	{
		OPTICK_EVENT();
		VkRect2D scissor{};
		scissor.offset = { 0, 0 };
		scissor.extent = extent;
		vkCmdSetScissor(m_command_buffers[current_frame], first_scissor_index, scissor_count, &scissor);
	}
	void CommandBuffer::draw(uint32_t current_frame, uint32_t vertex_count, uint32_t instance_count, uint32_t first_vertex_index, uint32_t first_instance_index)
	{
		// draw vertex buffer
		OPTICK_EVENT();
		vkCmdDraw(m_command_buffers[current_frame], vertex_count, instance_count, first_vertex_index, first_instance_index);
	}
	void CommandBuffer::draw(uint32_t current_frame, uint32_t index_count, uint32_t instance_count, uint32_t first_index, uint32_t vertex_offset, uint32_t first_instance)
	{
		// draw vertex by index buffer
		OPTICK_EVENT();
		vkCmdDrawIndexed(m_command_buffers[current_frame], index_count, instance_count, first_index, vertex_offset, first_instance);
	}
	void CommandBuffer::bindVertexBuffer(uint32_t current_frame, VertexBuffer& buffer, VkDeviceSize* offset, uint32_t first_binding_index, uint32_t binding_count)
	{
		OPTICK_EVENT();
		VkBuffer vertex_buffers[] = { buffer.getHandle() };
		vkCmdBindVertexBuffers(m_command_buffers[current_frame], first_binding_index, binding_count, vertex_buffers, offset);
	}
	void CommandBuffer::bindIndexBuffer(uint32_t current_frame, IndexBuffer& buffer, VkDeviceSize offset, VkIndexType index_type)
	{
		OPTICK_EVENT();
		vkCmdBindIndexBuffer(m_command_buffers[current_frame], buffer.getHandle(), offset, index_type);
	}
	void CommandBuffer::bindDescriptorSets(uint32_t current_frame, VkPipelineBindPoint bind_point, VkPipelineLayout layout, const std::vector<VkDescriptorSet> descriptor_sets, uint32_t first_set_index, uint32_t descriptor_set_count, uint32_t offset)
	{
		OPTICK_EVENT();
		vkCmdBindDescriptorSets(m_command_buffers[current_frame], bind_point, layout, first_set_index, descriptor_set_count, descriptor_sets.data(), 1, &offset);
	}
}