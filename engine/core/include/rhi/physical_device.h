#pragma once

#include <set>
#include <string>
#include <vulkan/vulkan.h>
#include "instance.h"
#include <optional>
#include "include/common/queue_family_indices.h"
#include "include/common/swap_chain_support_details.h"

namespace ToolEngine
{
	class PhysicalDevice
	{
	public:
		PhysicalDevice(Instance& instance, VkSurfaceKHR& surface);
		~PhysicalDevice();

		VkPhysicalDevice getHandle() const { return m_physical_device; }

		// not all graphics cards can present image (such as AI card), so we should check whether swapchain is supported 
		const std::vector<const char*> m_device_extensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

	private:
		VkPhysicalDevice m_physical_device{ VK_NULL_HANDLE };
		VkSurfaceKHR& m_surface_handle;

		bool checkDeviceSupport(VkPhysicalDevice device);
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	};
}