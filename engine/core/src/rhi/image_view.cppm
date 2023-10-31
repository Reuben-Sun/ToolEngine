#include <vulkan/vulkan.h>
#include "include/rhi/device.h"
#include "include/common/macro.h"
import ImageView;

namespace ToolEngine
{
	ImageView::ImageView(Device& device, VkImage image, VkFormat format, VkImageAspectFlags aspect_flags)
        : m_device(device), m_image(image), m_format(format)
	{
        VkImageViewCreateInfo create_info{};
        create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        create_info.image = m_image;
        create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
        create_info.format = m_format;
        create_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        create_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        create_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        create_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        create_info.subresourceRange.aspectMask = aspect_flags;
        create_info.subresourceRange.baseMipLevel = 0;
        create_info.subresourceRange.levelCount = 1;
        create_info.subresourceRange.baseArrayLayer = 0;
        create_info.subresourceRange.layerCount = 1;
        if (vkCreateImageView(m_device.getHandle(), &create_info, nullptr, &m_image_view) != VK_SUCCESS)
        {
            LOG_ERROR("failed to create image views!");
        }
	}
	ImageView::~ImageView()
	{
        if (m_image_view != VK_NULL_HANDLE)
        {
			vkDestroyImageView(m_device.getHandle(), m_image_view, nullptr);
		}
	}
}