#pragma once
#include <cstdint>
#include <optional>
#include <vulkan/vulkan.h>
#include <vector>

namespace ToolEngine
{
    // queue is a container of gpu command, these indices mean which subset command this queue allow
    struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphics_family;
		std::optional<uint32_t> present_family;

		bool isComplete()
		{
			return graphics_family.has_value() && present_family.has_value();
		}

        static QueueFamilyIndices getQueueFamilyIndices(VkPhysicalDevice device, VkSurfaceKHR surface)
        {
            QueueFamilyIndices indices;

            uint32_t queue_family_count = 0;
            vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, nullptr);
            std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
            vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, queue_families.data());

            // find one and only one queue which suport VK_QUEUE_GRAPHICS_BIT
            int family_index = 0;
            for (const auto& queue_family : queue_families)
            {
                if (queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT)
                {
                    indices.graphics_family = family_index;
                }
                VkBool32 present_support = false;
                vkGetPhysicalDeviceSurfaceSupportKHR(device, family_index, surface, &present_support);
                if (present_support)
                {
                    indices.present_family = family_index;
                }
                if (indices.isComplete())
                {
                    break;
                }
                family_index++;
            }

            return indices;
        }
	};
}