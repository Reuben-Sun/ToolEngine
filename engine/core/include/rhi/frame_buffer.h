#pragma once

#include <vulkan/vulkan.h>
#include "device.h"
#include "image_view.h"

namespace ToolEngine
{
	class FrameBuffer
	{
	public:
		FrameBuffer(Device& device, VkRenderPass render_pass, ImageView& image_view, uint32_t width, uint32_t height);
		~FrameBuffer();

		VkFramebuffer getHandle() { return m_frame_buffer; }

	private:
		VkFramebuffer m_frame_buffer;

		Device& m_device;
		VkRenderPass& m_render_pass;
		ImageView& m_image_view;
		uint32_t m_width;
		uint32_t m_height;
	};
}