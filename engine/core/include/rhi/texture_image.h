#pragma once

#include <vulkan/vulkan.h>
#include <string>
#include "buffer.h"
#include "device.h"
#include "physical_device.h"
#include "image.h"
#include "include/rhi/single_time_command_buffer.h"

import Global_Context;

namespace ToolEngine
{
	class TextureImage : Buffer
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