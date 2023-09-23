#pragma once

#include <vulkan/vulkan.h>
#include "include/common/depth_support_details.h"
#include "image_view.h"	
#include "device.h"
#include "physical_device.h"
#include "image.h"

namespace ToolEngine
{
	class DepthResources
	{
	public:
		DepthResources(Device& device, PhysicalDevice& physical_device, VkExtent2D extent);
		~DepthResources();

		ImageView& getImageView() { return *m_depth_image_view; }

	private:
		std::unique_ptr<Image> m_depth_image;
		std::unique_ptr<ImageView> m_depth_image_view;
		Device& m_device;
		PhysicalDevice& m_physical_device;
	};
}