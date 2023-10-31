#include <vulkan/vulkan.h>
#include "device.h"
#include "image_view.h"

export module FrameBuffer;

namespace ToolEngine
{
	export class FrameBuffer
	{
	public:
		FrameBuffer(Device& device, VkRenderPass render_pass, ImageView& swap_chain_image_view, ImageView& depth_image_view, uint32_t width, uint32_t height);
		~FrameBuffer();

		VkFramebuffer getHandle() { return m_frame_buffer; }

	private:
		VkFramebuffer m_frame_buffer;

		Device& m_device;
		VkRenderPass& m_render_pass;
		ImageView& m_swap_chain_image_view;
		ImageView& m_depth_image_view;
		uint32_t m_width;
		uint32_t m_height;
	};
}