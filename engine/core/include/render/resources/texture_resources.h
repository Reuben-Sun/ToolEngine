#pragma once

#include <vulkan/vulkan.h>
#include "include/rhi/device.h"
#include "include/rhi/physical_device.h"
#include "render_resources.h"

namespace ToolEngine
{
	class TextureResources: public RenderResources
	{
	public:
		TextureResources(Device& device, PhysicalDevice& physical_device, VkExtent2D extent);
		~TextureResources();
	};
}