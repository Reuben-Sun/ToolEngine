#include <vulkan/vulkan.h>
#include "include/rhi/device.h"

import RenderResources;
import ImageView;
import Image;
import PhysicalDevice;

namespace ToolEngine
{
	RenderResources::RenderResources(Device& device, PhysicalDevice& physical_device)
		: m_device(device), m_physical_device(physical_device)
	{
	}
	RenderResources::~RenderResources()
	{
	}
}
