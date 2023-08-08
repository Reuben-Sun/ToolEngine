#pragma once

#include <string>
#include <vector>
#include<unordered_map>
#include <vulkan/vulkan.h>

namespace ToolEngine
{
	class Instance
	{
	public:
		Instance(const std::unordered_map<const char*, bool>& required_extensions = {});
		~Instance();
	private:
		VkInstance m_instance;
		std::vector<const char*> m_enabled_extensions;
	};
}