#include "include/rhi/instance.h"

namespace ToolEngine
{
	Instance::Instance(const std::string& app_name, std::vector<const char*> required_extensions)
	{
		// TODO: check if all required extensions are available
		m_enabled_extensions = required_extensions;

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = app_name.c_str();
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Tool Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        createInfo.enabledExtensionCount = m_enabled_extensions.size();
        createInfo.ppEnabledExtensionNames = m_enabled_extensions.data();

        createInfo.enabledLayerCount = 0;

        if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS) 
        {
            throw std::runtime_error("failed to create instance!");
        }
	}

	Instance::~Instance()
	{
		if (m_instance != VK_NULL_HANDLE) 
		{
			vkDestroyInstance(m_instance, nullptr);
		}
	}
}



