#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <unordered_map>
#include <vulkan/vulkan.h>
#include <iostream>

import DebugUtils;

namespace ToolEngine
{
	class Instance
	{
	public:
		Instance(const std::string& app_name, std::vector<const char*> required_extensions, bool enable_validation_layers = true);
		~Instance();

		VkInstance getHandle() const { return m_instance; }
		bool isValidationLayersEnabled() const { return m_enable_validation_layers; }
		const std::vector<const char*> m_validation_layers = { "VK_LAYER_KHRONOS_validation" };
	private:
		VkInstance m_instance;
		VkDebugUtilsMessengerEXT debug_utils_messenger{ VK_NULL_HANDLE };
		std::vector<const char*> m_enabled_extensions;
		bool m_enable_validation_layers;

		bool checkValidationLayerSupport();
	};
}