#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include<unordered_map>
#include <vulkan/vulkan.h>

namespace ToolEngine
{
	class Instance
	{
	public:
		Instance(const std::string& app_name, std::vector<const char*> required_extensions);
		~Instance();

		VkInstance getHandle() const { return m_instance; }
	private:
		VkInstance m_instance;
		std::vector<const char*> m_enabled_extensions;
	};
}