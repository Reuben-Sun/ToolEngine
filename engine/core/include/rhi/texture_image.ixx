#include <vulkan/vulkan.h>

export module TextureImage;

import Global_Context;
import Buffer;
import Image;
import SingleTimeCommandBuffer;
import PhysicalDevice;
import Device;
import <string>;
import <memory>;

namespace ToolEngine
{
	export class TextureImage
	{
	public:
		TextureImage(Device& device, PhysicalDevice& physical_device, std::string file_path);
		~TextureImage();
		VkImage getHandle() const { return m_texture_image->getHandle(); }
		VkFormat getFormat() const { return m_texture_image->getFormat(); }

	private:
		std::unique_ptr<Image> m_texture_image;
		Device& m_device;
		PhysicalDevice& m_physical_device;
		void createImageFormBuffer(VkBuffer buffer, uint32_t width, uint32_t height);
	};
}