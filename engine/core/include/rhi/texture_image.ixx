#include <vulkan/vulkan.h>
#include "device.h"
#include "physical_device.h"

export module TextureImage;

import Global_Context;
import Buffer;
import Image;
import SingleTimeCommandBuffer;
import <string>;
import <memory>;

namespace ToolEngine
{
	export class TextureImage : Buffer
	{
	public:
		TextureImage(Device& device, PhysicalDevice& physical_device, std::string file_path);
		~TextureImage();
		VkImage getHandle() const { return m_texture_image->getHandle(); }
		VkFormat getFormat() const { return m_texture_image->getFormat(); }

	private:
		std::unique_ptr<Image> m_texture_image;

		void createImageFormBuffer(VkBuffer buffer, uint32_t width, uint32_t height);
	};
}