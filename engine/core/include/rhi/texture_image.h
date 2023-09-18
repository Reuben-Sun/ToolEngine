#pragma once

#include <vulkan/vulkan.h>
#include <string>
#include "buffer.h"
#include "device.h"
#include "physical_device.h"
#include "include/file/file_utils.h"
#include "include/rhi/single_time_command_buffer.h"

namespace ToolEngine
{
	class TextureImage : Buffer
	{
	public:
		TextureImage(Device& device, PhysicalDevice& physical_device, std::string file_path);
		~TextureImage();
		VkImage getHandle() const { return m_texture_image; }
		VkFormat getFormat() const { return m_format; }

		void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties);
		
		
	private:
		VkImage m_texture_image;
		VkDeviceMemory m_texture_image_memory;
		VkFormat m_format = VK_FORMAT_R8G8B8A8_SRGB;

		void transitionImageLayout(VkImageLayout old_layout, VkImageLayout new_layout);
		void createImageFormBuffer(VkBuffer buffer, uint32_t width, uint32_t height);
	};
}