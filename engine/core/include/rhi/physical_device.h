#pragma once

#include <set>
#include <string>
#include <vulkan/vulkan.h>
#include "instance.h"
#include <optional>

namespace ToolEngine
{
	class PhysicalDevice
	{
	public:
		PhysicalDevice(Instance& instance, VkSurfaceKHR& surface);
		~PhysicalDevice();

		struct QueueFamilyIndices
		{
			std::optional<uint32_t> graphics_family;
			std::optional<uint32_t> present_family;

			bool isComplete()
			{
				return graphics_family.has_value() && present_family.has_value();
			}
		};

		struct SwapChainSupportDetails
		{
			VkSurfaceCapabilitiesKHR capabilities;
			std::vector<VkSurfaceFormatKHR> formats;
			std::vector<VkPresentModeKHR> presentModes;
		};

		VkPhysicalDevice getPhysicalDevice() const { return m_physical_device; }

	private:
		VkPhysicalDevice m_physical_device{ VK_NULL_HANDLE };
		VkSurfaceKHR& m_surface_handle;

		// not all graphics cards can present image (such as AI card), so we should check whether swapchain is supported 
		const std::vector<const char*> m_device_extensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
		bool checkDeviceSupport(VkPhysicalDevice device);
		QueueFamilyIndices getQueueFamilyIndices(VkPhysicalDevice device);
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);
		SwapChainSupportDetails getSwapChainSupportDetails(VkPhysicalDevice device);
	};
}