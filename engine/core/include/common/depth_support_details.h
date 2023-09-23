#pragma once

#include <vulkan/vulkan.h>
#include "include/rhi/physical_device.h"

namespace ToolEngine
{
	struct DepthSupportDetails
	{
		VkFormat support_format;

        static DepthSupportDetails getDepthSupportDetails(VkPhysicalDevice physical_device)
		{
			DepthSupportDetails details;
			VkFormat depth_format = VK_FORMAT_UNDEFINED;

			VkFormat formats[] = { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT };
			for (VkFormat format : formats)
			{
				VkFormatProperties props;
				vkGetPhysicalDeviceFormatProperties(physical_device, format, &props);

				if (props.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
				{
					depth_format = format;
					break;
				}
			}
			details.support_format = depth_format;
			return details;
		}





	};
}



