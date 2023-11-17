#include "include/common/macro.h"
import DebugUtils;

namespace ToolEngine
{
    VkResult DebugUtils::createDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* create_info, const VkAllocationCallbacks* allocator, VkDebugUtilsMessengerEXT* debug_messenger)
    {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr)
        {
            return func(instance, create_info, allocator, debug_messenger);
        }
        else
        {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void DebugUtils::destroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debug_messenger, const VkAllocationCallbacks* allocator)
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr)
        {
            func(instance, debug_messenger, allocator);
        }
    }

    VKAPI_ATTR VkBool32 VKAPI_CALL DebugUtils::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity, VkDebugUtilsMessageTypeFlagsEXT message_type, const VkDebugUtilsMessengerCallbackDataEXT* callback_data, void* user_data)
    {
        LOG_INFO("Vulkan validation layer: {}", callback_data->pMessage);
        return VK_FALSE;
    }
    void DebugUtils::beginDebugUtilsLabelEXT(VkCommandBuffer cmd, std::string label)
    {
        //VkDebugUtilsLabelEXT label_info = {};
        //label_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
        //label_info.pLabelName = label.c_str();
        //vkCmdBeginDebugUtilsLabelEXT(cmd, &label_info);
    }
    void DebugUtils::endDebugUtilsLabelEXT(VkCommandBuffer cmd)
    {
        //vkCmdEndDebugUtilsLabelEXT(cmd);
    }
}