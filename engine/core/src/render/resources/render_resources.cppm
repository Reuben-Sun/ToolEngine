#include <vulkan/vulkan.h>
#include "include/rhi/device.h"
#include "include/rhi/physical_device.h"
#include "include/rhi/image.h"
import RenderResources;
import ImageView;

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
