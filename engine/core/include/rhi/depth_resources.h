#pragma once

#include <vulkan/vulkan.h>
#include "include/common/depth_support_details.h"
#include "image_view.h"	
#include "device.h"

namespace ToolEngine
{
	class DepthResources
	{
	public:
		DepthResources(Device& device, DepthSupportDetails depth_details, VkExtent2D extent);
		~DepthResources();

		ImageView& getImageView() { return *m_depth_image_view; }

	private:
		VkImage m_depth_image;
		std::unique_ptr<ImageView> m_depth_image_view;
		Device& m_device;
	};
}