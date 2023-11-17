#include "include/common/macro.h"

export module PhysicalDevice;

import Instance;
import QueueFamilyIndices;
import SwapChainSupportDetails;

namespace ToolEngine
{
	export class PhysicalDevice
	{
	public:
		PhysicalDevice(Instance& instance, VkSurfaceKHR& surface);
		~PhysicalDevice();

		VkPhysicalDevice getHandle() const { return m_physical_device; }
		VkBool32 checkPresentSupported(VkSurfaceKHR surface, uint32_t queue_family_index) const;

		// not all graphics cards can present image (such as AI card), so we should check whether swapchain is supported 
		const std::vector<const char*> m_device_extensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

	private:
		VkPhysicalDevice m_physical_device{ VK_NULL_HANDLE };
		VkSurfaceKHR& m_surface_handle;

		bool checkDeviceSupport(VkPhysicalDevice device);
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	};
}