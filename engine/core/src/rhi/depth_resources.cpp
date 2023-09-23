#include "include/rhi/depth_resources.h"

namespace ToolEngine
{
	DepthResources::DepthResources(Device& device, PhysicalDevice& physical_device, VkExtent2D extent)
		: m_device(device), m_physical_device(physical_device)
	{
		DepthSupportDetails depth_support_details = DepthSupportDetails::getDepthSupportDetails(m_physical_device.getHandle());
		m_depth_image = std::make_unique<Image>(m_device, m_physical_device, extent, depth_support_details.support_format, 
			VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

	}
	DepthResources::~DepthResources()
	{
	}
}