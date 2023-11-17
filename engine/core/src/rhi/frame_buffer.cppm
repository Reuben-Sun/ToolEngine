#include "include/common/macro.h"
import FrameBuffer;
import ImageView;
import Device;

namespace ToolEngine
{
	FrameBuffer::FrameBuffer(Device& device, VkRenderPass render_pass, ImageView& swap_chain_image_view, ImageView& depth_image_view, uint32_t width, uint32_t height):
		m_device(device), m_render_pass(render_pass), m_swap_chain_image_view(swap_chain_image_view), m_depth_image_view(depth_image_view), m_width(width), m_height(height)
	{
        std::array<VkImageView, 2> attachments = { m_swap_chain_image_view.getHandle(), m_depth_image_view.getHandle()};

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = m_render_pass;
        framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
        framebufferInfo.pAttachments = attachments.data();
        framebufferInfo.width = m_width;
        framebufferInfo.height = m_height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(m_device.getHandle(), &framebufferInfo, nullptr, &m_frame_buffer) != VK_SUCCESS)
        {
            LOG_ERROR("failed to create framebuffer!");
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