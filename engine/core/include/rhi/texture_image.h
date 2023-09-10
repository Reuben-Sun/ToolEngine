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
	private:

	};
}