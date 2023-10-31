#include <vulkan/vulkan.h>
#include "device.h"

export module SwapChain;

import SwapChainSupportDetails;
import PhysicalDevice;
import <vector>;
import <algorithm>;

namespace ToolEngine
{
	export class SwapChain
	{
	public:
		SwapChain(Device& device, PhysicalDevice& physical_device, VkSurfaceKHR& surface, VkExtent2D extent);
		~SwapChain();

		VkSwapchainKHR getHandle() const { return m_swap_chain; }
		VkFormat getFormat() const { return m_swap_chain_image_format; }
		VkExtent2D getExtent() const { return m_swap_chain_extent; }
		std::vector<VkImage> getImages() const { return m_swap_chain_images; }
		float getWidthDividedByHeight() const { return static_cast<float>(m_swap_chain_extent.width) / static_cast<float>(m_swap_chain_extent.height); }

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