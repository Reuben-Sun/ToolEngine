#include <vulkan/vulkan.h>
#include "physical_device.h"

export module DepthSupportDetails;

namespace ToolEngine
{
	export struct DepthSupportDetails
	{
		VkFormat support_format;

		static DepthSupportDetails getDepthSupportDetails(VkPhysicalDevice physical_device);
	};
}



