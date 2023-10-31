#include <vulkan/vulkan.h>
#include "device.h"
#include "physical_device.h"

export module Image;
import SingleTimeCommandBuffer;

namespace ToolEngine
{
	export class Image
	{
	public:
		Image(Device& device, PhysicalDevice& physical_device, VkExtent2D extent, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties);
		~Image();

		void transitionImageLayout(VkImageLayout old_layout, VkImageLayout new_layout);

		VkImage getHandle() const { return m_image; }
		VkFormat getFormat() const { return m_format; }
	private:
		VkImage m_image{ VK_NULL_HANDLE };
		VkDeviceMemory m_image_memory{ VK_NULL_HANDLE };
		VkFormat m_format = VK_FORMAT_R8G8B8A8_SRGB;

		Device& m_device;
		PhysicalDevice& m_physical_device;
		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	};
}