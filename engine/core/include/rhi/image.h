#pragma once

#include <vulkan/vulkan.h>
#include "device.h"
#include "physical_device.h"

namespace ToolEngine
{
	class Image
	{
	public:
		Image(Device& device, PhysicalDevice& physical_device, VkExtent2D extent, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties);
		~Image();

		VkImage getHandle() const { return m_image; }
	private:
		VkImage m_image{ VK_NULL_HANDLE };
		VkDeviceMemory m_image_memory{ VK_NULL_HANDLE };
		VkFormat m_format = VK_FORMAT_R8G8B8A8_SRGB;

		Device& m_device;
		PhysicalDevice& m_physical_device;
		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	};
}