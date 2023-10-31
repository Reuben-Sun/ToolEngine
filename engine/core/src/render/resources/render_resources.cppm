#include <vulkan/vulkan.h>

import RenderResources;
import ImageView;
import Image;
import PhysicalDevice;
import Device;

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
