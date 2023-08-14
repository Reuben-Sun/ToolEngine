#pragma once

#include <vulkan/vulkan.h>
#include "device.h"

namespace ToolEngine
{
	class ImageView
	{
	public:
		ImageView(Device& device, VkImage& image, VkFormat format);
		~ImageView();

		VkImageView getHandle() { return m_image_view; }

	private:
		VkImageView m_image_view;

		Device& m_device;
		VkImage& m_image;
		VkFormat& m_format;
	};
}