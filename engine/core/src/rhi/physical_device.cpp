#include "include/rhi/physical_device.h"

namespace ToolEngine
{
	PhysicalDevice::PhysicalDevice(Instance& instance, VkSurfaceKHR& surface): m_surface_handle(surface)
	{
        uint32_t device_count = 0;
        vkEnumeratePhysicalDevices(instance.getHandle(), &device_count, nullptr);
        if (device_count == 0) 
        {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
        }
        std::vector<VkPhysicalDevice> devices(device_count);
        vkEnumeratePhysicalDevices(instance.getHandle(), &device_count, devices.data());

        for (const auto& device : devices)
        {
            if (checkDeviceSupport(device))
            {
                m_physical_device = device;
                break;
            }
        }

        if (m_physical_device == VK_NULL_HANDLE)
        {
            throw std::runtime_error("failed to find a suitable GPU!");
        }
	}

    PhysicalDevice::~PhysicalDevice()
    {
    }

    bool PhysicalDevice::checkDeviceSupport(VkPhysicalDevice device)
    {
        QueueFamilyIndices indices = getQueueFamilyIndices(device);
        bool extension_supported = checkDeviceExtensionSupport(device);
        bool swap_chain_adequate = false;
        if (extension_supported)
        {
            SwapChainSupportDetails swap_chain_support = getSwapChainSupportDetails(device);
            swap_chain_adequate = !swap_chain_support.formats.empty() && !swap_chain_support.presentModes.empty();
        }
        return indices.isComplete() && extension_supported && swap_chain_adequate;
    }

    QueueFamilyIndices PhysicalDevice::getQueueFamilyIndices(VkPhysicalDevice device)
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
            vkGetPhysicalDeviceSurfaceSupportKHR(device, family_index, m_surface_handle, &present_support);
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

    bool PhysicalDevice::checkDeviceExtensionSupport(VkPhysicalDevice device)
    {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());
        std::set<std::string> requiredExtensions(m_device_extensions.begin(), m_device_extensions.end());
        for (const auto& extension : availableExtensions)
        {
            requiredExtensions.erase(extension.extensionName);
        }
        return requiredExtensions.empty();
    }

    SwapChainSupportDetails PhysicalDevice::getSwapChainSupportDetails(VkPhysicalDevice device)
    {
        SwapChainSupportDetails details;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_surface_handle, &details.capabilities);
        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface_handle, &formatCount, nullptr);
        if (formatCount != 0)
        {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface_handle, &formatCount, details.formats.data());
        }
        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface_handle, &presentModeCount, nullptr);
        if (presentModeCount != 0)
        {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface_handle, &presentModeCount, details.presentModes.data());
        }
        return details;
    }
}