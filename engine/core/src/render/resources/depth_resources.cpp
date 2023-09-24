#include "include/render/resources/depth_resources.h"

namespace ToolEngine
{
	DepthResources::DepthResources(Device& device, PhysicalDevice& physical_device, VkExtent2D extent)
		: RenderResources(device, physical_device)
	{
		DepthSupportDetails depth_support_details = DepthSupportDetails::getDepthSupportDetails(m_physical_device.getHandle());
		m_image = std::make_unique<Image>(m_device, m_physical_device, extent, depth_support_details.support_format,
			VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		m_image_view = std::make_unique<ImageView>(m_device, m_image->getHandle(), depth_support_details.support_format, VK_IMAGE_ASPECT_DEPTH_BIT);
		m_image->transitionImageLayout(VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
	}
	DepthResources::~DepthResources()
	{

	}
}