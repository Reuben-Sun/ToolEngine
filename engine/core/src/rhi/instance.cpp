#include "include/rhi/instance.h"

namespace ToolEngine
{
	Instance::Instance(const std::string& app_name, std::vector<const char*> required_extensions, bool enable_validation_layers)
		: m_instance(VK_NULL_HANDLE), m_enabled_extensions(required_extensions), m_enable_validation_layers(enable_validation_layers)
	{
        if (m_enable_validation_layers && !checkValidationLayerSupport())
        {
            throw std::runtime_error("validation layers requested, but not available!");
        }
        if (m_enable_validation_layers)
        {
			m_enabled_extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}

        VkApplicationInfo app_info{};
        app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        app_info.pApplicationName = app_name.c_str();
        app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        app_info.pEngineName = "Tool Engine";
        app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        app_info.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo create_info{};
        create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        create_info.pApplicationInfo = &app_info;
        create_info.enabledExtensionCount = static_cast<uint32_t>(m_enabled_extensions.size());
        create_info.ppEnabledExtensionNames = m_enabled_extensions.data();

        if (m_enable_validation_layers) 
        {
            create_info.enabledLayerCount = static_cast<uint32_t>(m_validation_layers.size());
            create_info.ppEnabledLayerNames = m_validation_layers.data();

            VkDebugUtilsMessengerCreateInfoEXT debug_create_info;
            debug_create_info = {};
            debug_create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            debug_create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            debug_create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
            debug_create_info.pfnUserCallback = DebugUtils::debugCallback;

            create_info.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debug_create_info;
        }
        else
        {
            create_info.enabledLayerCount = 0;
            create_info.pNext = nullptr;
        }

        if (vkCreateInstance(&create_info, nullptr, &m_instance) != VK_SUCCESS) 
        {
            throw std::runtime_error("failed to create instance!");
        }

        if (m_enable_validation_layers)
        {
			VkDebugUtilsMessengerCreateInfoEXT debug_create_info;
			debug_create_info = {};
			debug_create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
			debug_create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
			debug_create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
			debug_create_info.pfnUserCallback = DebugUtils::debugCallback;

            if (DebugUtils::createDebugUtilsMessengerEXT(m_instance, &debug_create_info, nullptr, &debug_utils_messenger) != VK_SUCCESS)
            {
				throw std::runtime_error("failed to set up debug messenger!");
			}
		}
	}

	Instance::~Instance()
	{
        if (m_enable_validation_layers)
        {
            DebugUtils::destroyDebugUtilsMessengerEXT(m_instance, debug_utils_messenger, nullptr);
        }

		if (m_instance != VK_NULL_HANDLE) 
		{
			vkDestroyInstance(m_instance, nullptr);
		}
	}

    bool Instance::checkValidationLayerSupport()
    {
        uint32_t layer_count;
        vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

        std::vector<VkLayerProperties> available_layers(layer_count);
        vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());

        for (const char* layer_name : m_validation_layers)
        {
            bool layer_found = false;
            for (const auto& layer_properties : available_layers)
            {
                if (strcmp(layer_name, layer_properties.layerName) == 0)
                {
                    layer_found = true;
                    break;
                }
            }
            if (!layer_found)
            {
                return false;
            }
        }

        return true;
    }

   
}



