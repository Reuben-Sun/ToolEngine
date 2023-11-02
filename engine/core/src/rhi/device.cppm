#include <vulkan/vulkan.h>
#include "include/common/macro.h"

import Device;
import Queue;
import CommandPool;
import Instance;
import QueueFamilyIndices;
import PhysicalDevice;
import <memory>;
import <set>;
import <optick.h>;

namespace ToolEngine
{
    Device::Device(Instance& instance, PhysicalDevice& physical_device, VkSurfaceKHR& surface)
    {
        m_queue_family_indices = QueueFamilyIndices::getQueueFamilyIndices(physical_device.getHandle(), surface);

        std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
        std::set<uint32_t> unique_queue_families =
        {
            m_queue_family_indices.graphics_family.value(),
            m_queue_family_indices.present_family.value()
        };
        float queuePriority = 1.0f;
        for (uint32_t queue_family_index : unique_queue_families)
        {
            VkDeviceQueueCreateInfo queue_create_info{};
            queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queue_create_info.queueFamilyIndex = queue_family_index;
            queue_create_info.queueCount = 1;
            queue_create_info.pQueuePriorities = &queuePriority;
            queue_create_infos.push_back(queue_create_info);
        }

        VkPhysicalDeviceFeatures device_features{};
        device_features.samplerAnisotropy = VK_TRUE;

        VkDeviceCreateInfo create_info{};
        create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        create_info.queueCreateInfoCount = static_cast<uint32_t>(queue_create_infos.size());
        create_info.pQueueCreateInfos = queue_create_infos.data();
        create_info.pEnabledFeatures = &device_features;
        create_info.enabledExtensionCount = static_cast<uint32_t>(physical_device.m_device_extensions.size());
        create_info.ppEnabledExtensionNames = physical_device.m_device_extensions.data();

        if (instance.isValidationLayersEnabled())
        {
            create_info.enabledLayerCount = static_cast<uint32_t>(instance.m_validation_layers.size());
            create_info.ppEnabledLayerNames = instance.m_validation_layers.data();
        }
        else
        {
            create_info.enabledLayerCount = 0;
        }

        if (vkCreateDevice(physical_device.getHandle(), &create_info, nullptr, &m_device) != VK_SUCCESS)
        {
            LOG_ERROR("failed to create logical device!");
        }

        VkBool32 present_supported = physical_device.checkPresentSupported(surface, m_queue_family_indices.graphics_family.value());
        m_graphics_queue = std::make_unique<Queue>(m_device, m_queue_family_indices.graphics_family.value(), present_supported, 0);
        present_supported = physical_device.checkPresentSupported(surface, m_queue_family_indices.present_family.value());
        m_present_queue = std::make_unique<Queue>(m_device, m_queue_family_indices.present_family.value(), present_supported, 0);

        m_command_pool = std::make_unique<CommandPool>(m_device, m_queue_family_indices.graphics_family.value());
    }

    Device::~Device()
    {
        if(m_device != VK_NULL_HANDLE)
		{
			vkDestroyDevice(m_device, nullptr);
		}
    }
    void Device::present(VkSemaphore* wait_semaphores, uint32_t image_index, VkSwapchainKHR* swap_chains)
    {
        OPTICK_EVENT();
        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = wait_semaphores;

        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swap_chains;

        presentInfo.pImageIndices = &image_index;

        vkQueuePresentKHR(m_present_queue->getHandle(), &presentInfo);
    }
    Queue& Device::getGraphicsQueue() const { return *m_graphics_queue; }
    Queue& Device::getPresentQueue() const { return *m_present_queue; }
}