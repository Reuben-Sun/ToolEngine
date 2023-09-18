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

    VkBool32 PhysicalDevice::checkPresentSupported(VkSurfaceKHR surface, uint32_t queue_family_index) const
    {
        VkBool32 present_supported{ VK_FALSE };

        if (surface != VK_NULL_HANDLE)
        {
            vkGetPhysicalDeviceSurfaceSupportKHR(m_physical_device, queue_family_index, surface, &present_supported);
        }

        return present_supported;
    }

    bool PhysicalDevice::checkDeviceSupport(VkPhysicalDevice device)
    {
        QueueFamilyIndices indices = QueueFamilyIndices::getQueueFamilyIndices(device, m_surface_handle);
        bool extension_supported = checkDeviceExtensionSupport(device);
        bool swap_chain_adequate = false;
        if (extension_supported)
        {
            SwapChainSupportDetails swap_chain_support = SwapChainSupportDetails::getSwapChainSupportDetails(device, m_surface_handle);
            swap_chain_adequate = !swap_chain_support.formats.empty() && !swap_chain_support.presentModes.empty();
        }

        VkPhysicalDeviceFeatures supported_features;
        vkGetPhysicalDeviceFeatures(device, &supported_features);

        return indices.isComplete() && extension_supported && swap_chain_adequate && supported_features.samplerAnisotropy;
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
}