#include "include/common/macro.h"
#include <optick.h>

export module CommandBuffer;
import Device;
import RenderPass;
import FrameBuffer;
import VertexBuffer;
import IndexBuffer;

namespace ToolEngine
{
	export class CommandBuffer
	{
	public:
		CommandBuffer(Device& device, uint32_t buffer_count);
		~CommandBuffer();

		VkCommandBuffer getHandle(uint32_t index) const { return m_command_buffers[index]; }
		void resetCommandBuffer(uint32_t current_frame);
		void submitCommandBuffer(uint32_t current_frame, VkSemaphore* wait_semaphores, VkSemaphore* signal_semaphores, VkFence in_flight_fence);
		void beginRecord(uint32_t current_frame);
		void endRecord(uint32_t current_frame);
		void beginRenderPass(uint32_t current_frame, RenderPass& render_pass, FrameBuffer& frame_buffer, VkExtent2D extent);
		void endRenderPass(uint32_t current_frame);
		void bindPipeline(uint32_t current_frame, VkPipeline pipeline);
		void setViewport(uint32_t current_frame, VkExtent2D extent, float min_depth, float max_depth, uint32_t first_viewport_index, uint32_t viewport_count);
		void setScissor(uint32_t current_frame, VkExtent2D extent, uint32_t first_scissor_index, uint32_t scissor_count);
		void draw(uint32_t current_frame, uint32_t vertex_count, uint32_t instance_count, uint32_t first_vertex_index, uint32_t first_instance_index);
		void draw(uint32_t current_frame, uint32_t index_count, uint32_t instance_count, uint32_t first_index, uint32_t vertex_offset, uint32_t first_instance);
		void bindVertexBuffer(uint32_t current_frame, VertexBuffer& buffer, VkDeviceSize* offset, uint32_t first_binding_index, uint32_t binding_count);
		void bindIndexBuffer(uint32_t current_frame, IndexBuffer& buffer, VkDeviceSize offset, VkIndexType index_type);
		void bindDescriptorSets(uint32_t current_frame, VkPipelineBindPoint bind_point, VkPipelineLayout layout, const std::vector<VkDescriptorSet> descriptor_sets, uint32_t first_set_index, uint32_t descriptor_set_count);
	private:
		std::vector<VkCommandBuffer> m_command_buffers;
		Device& m_device;
		uint32_t m_buffer_count;
	};
}