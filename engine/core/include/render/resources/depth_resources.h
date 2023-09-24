#pragma once

#include <vulkan/vulkan.h>
#include "include/rhi/device.h"
#include "include/rhi/physical_device.h"
#include "render_resources.h"
#include "include/common/depth_support_details.h"

namespace ToolEngine
{
	class DepthResources : public RenderResources
	{
	public:
		DepthResources(Device& device, PhysicalDevice& physical_device, VkExtent2D extent);
		~DepthResources();
	};
}