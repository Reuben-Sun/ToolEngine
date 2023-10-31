#pragma once

#include <vulkan/vulkan.h>
#include "include/rhi/device.h"
#include "include/rhi/physical_device.h"

export module DepthResources;
import RenderResources;
import DepthSupportDetails;

namespace ToolEngine
{
	export class DepthResources : public RenderResources
	{
	public:
		DepthResources(Device& device, PhysicalDevice& physical_device, VkExtent2D extent);
		~DepthResources();
	};
}