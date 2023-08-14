#pragma once

#include <vector>
#include <algorithm>
#include <vulkan/vulkan.h>
#include "device.h"
#include "physical_device.h"
#include "include/common/swap_chain_support_details.h"

namespace ToolEngine
{
	class SwapChain
	{
	public:
		SwapChain(Device& device, PhysicalDevice& physical_device, VkSurfaceKHR& surface, VkExtent2D extent);
		~SwapChain();

		VkSwapchainKHR getHandle() const { return m_swap_chain; }
		VkFormat getFormat() const { return m_swap_chain_image_format; }
		VkExtent2D getExtent() const { return m_swap_chain_extent; }
		std::vector<VkImage> getImages() const { return m_swap_chain_images; }

	private:
		VkSurfaceKHR m_surface;
		VkSwapchainKHR m_swap_chain;
		std::vector<VkImage> m_swap_chain_images;
		VkFormat m_swap_chain_image_format;
		VkExtent2D m_swap_chain_extent;

		Device& m_device;

		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& available_formats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& available_present_modes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, VkExtent2D app_extent);
	};
}			