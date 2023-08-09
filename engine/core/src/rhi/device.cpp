#include "include/rhi/device.h"

namespace ToolEngine
{
    Device::Device(Instance& instance, PhysicalDevice& physical_device, VkSurfaceKHR& surface)
    {
        QueueFamilyIndices indices = QueueFamilyIndices::getQueueFamilyIndices(physical_device.getHandle(), surface);

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies =
        {
            indices.graphics_family.value(),
            indices.present_family.value()
        };
        float queuePriority = 1.0f;
        for (uint32_t queueFamilyIndex : uniqueQueueFamilies)
        {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures{};

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.pEnabledFeatures = &deviceFeatures;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(physical_device.m_device_extensions.size());
        createInfo.ppEnabledExtensionNames = physical_device.m_device_extensions.data();

        if (instance.isValidationLayersEnabled())
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(instance.m_validation_layers.size());
            createInfo.ppEnabledLayerNames = instance.m_validation_layers.data();
        }
        else
        {
            createInfo.enabledLayerCount = 0;
        }

        if (vkCreateDevice(physical_device.getHandle(), &createInfo, nullptr, &m_device) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create logical device!");
        }

        VkBool32 present_supported = physical_device.checkPresentSupported(surface, indices.graphics_family.value());
        m_graphics_queue = std::make_unique<Queue>(m_device, indices.graphics_family.value(), present_supported, 0);
        present_supported = physical_device.checkPresentSupported(surface, indices.present_family.value());
        m_present_queue = std::make_unique<Queue>(m_device, indices.present_family.value(), present_supported, 0);
    }

    Device::~Device()
    {
        if(m_device != VK_NULL_HANDLE)
		{
			vkDestroyDevice(m_device, nullptr);
		}
    }
}