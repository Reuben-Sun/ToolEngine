#include <vulkan/vulkan.h>

export module SwapChainSupportDetails;
import <vector>;

namespace ToolEngine
{
    export struct SwapChainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;

		static SwapChainSupportDetails getSwapChainSupportDetails(VkPhysicalDevice physical_device, VkSurfaceKHR surface);
	};
}