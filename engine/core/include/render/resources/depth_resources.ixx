#pragma once

#include <vulkan/vulkan.h>
#include "include/rhi/device.h"

export module DepthResources;
import RenderResources;
import DepthSupportDetails;
import PhysicalDevice;

namespace ToolEngine
{
	export class DepthResources : public RenderResources
	{
	public:
		DepthResources(Device& device, PhysicalDevice& physical_device, VkExtent2D extent);
		~DepthResources();
	};
}