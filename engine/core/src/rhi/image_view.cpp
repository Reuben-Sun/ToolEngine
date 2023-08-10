#include "include/rhi/image_view.h"

namespace ToolEngine
{
	ImageView::ImageView(Device& device, VkImage& image, VkFormat format)
        : m_device(device), m_image(image), m_format(format)
	{
        VkImageViewCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = m_image;
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = m_format;
        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;
        if (vkCreateImageView(m_device.getHandle(), &createInfo, nullptr, &m_image_view) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create image views!");
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