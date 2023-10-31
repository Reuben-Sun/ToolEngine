#pragma once

#include <vulkan/vulkan.h>

export module DepthResources;
import RenderResources;
import DepthSupportDetails;
import PhysicalDevice;
import Device;

namespace ToolEngine
{
	export class DepthResources : public RenderResources
	{
	public:
		DepthResources(Device& device, PhysicalDevice& physical_device, VkExtent2D extent);
		~DepthResources();
	};
}