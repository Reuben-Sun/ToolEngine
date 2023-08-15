#include "include/rhi/frame_buffer.h"

namespace ToolEngine
{
	FrameBuffer::FrameBuffer(Device& device, VkRenderPass render_pass, ImageView& image_view, uint32_t width, uint32_t height):
		m_device(device), m_render_pass(render_pass), m_image_view(image_view), m_width(width), m_height(height)
	{
        VkImageView attachments[] = { m_image_view.getHandle() };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = m_render_pass;
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = m_width;
        framebufferInfo.height = m_height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(m_device.getHandle(), &framebufferInfo, nullptr, &m_frame_buffer) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create framebuffer!");
        }
	}
	FrameBuffer::~FrameBuffer()
	{
        if (m_frame_buffer != VK_NULL_HANDLE)
        {
			vkDestroyFramebuffer(m_device.getHandle(), m_frame_buffer, nullptr);
		}
	}
}