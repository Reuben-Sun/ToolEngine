#include "include/rhi/instance.h"

namespace ToolEngine
{
	Instance::Instance(const std::unordered_map<const char*, bool>& required_extensions)
	{
	}

	Instance::~Instance()
	{
		if (m_instance != VK_NULL_HANDLE) 
		{
			vkDestroyInstance(m_instance, nullptr);
		}
	}
}



