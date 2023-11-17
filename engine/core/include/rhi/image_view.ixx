#include "include/common/macro.h"

export module ImageView;
import Device;

namespace ToolEngine
{
	export class ImageView
	{
	public:
		ImageView(Device& device, VkImage image, VkFormat format, VkImageAspectFlags aspect_flags);
		~ImageView();

		VkImageView getHandle() { return m_image_view; }

	private:
		VkImageView m_image_view;

		Device& m_device;
		VkImage m_image;
		VkFormat& m_format;
	};
}