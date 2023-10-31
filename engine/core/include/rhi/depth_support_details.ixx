#include <vulkan/vulkan.h>

export module DepthSupportDetails;
import PhysicalDevice;

namespace ToolEngine
{
	export struct DepthSupportDetails
	{
		VkFormat support_format;

		static DepthSupportDetails getDepthSupportDetails(VkPhysicalDevice physical_device);
	};
}



