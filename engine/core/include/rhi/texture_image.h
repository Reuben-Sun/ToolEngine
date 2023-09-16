#pragma once

#include <vulkan/vulkan.h>

#include "buffer.h"
#include "device.h"
#include "physical_device.h"
#include "include/file/file_utils.h"

namespace ToolEngine
{
	class TextureImage : Buffer
	{
	public:
		TextureImage(Device& device, PhysicalDevice& physical_device);
		~TextureImage();
		VkImage getHandle() const { return m_texture_image; }

		void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties);
	private:
		VkImage m_texture_image;
		VkDeviceMemory m_texture_image_memory;
	};
}