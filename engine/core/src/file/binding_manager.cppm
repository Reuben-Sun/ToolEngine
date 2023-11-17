#include "include/common/macro.h"
import BindingManager;
import Device;
import DescriptorPool;

namespace ToolEngine
{
	BindingManager::BindingManager(Device& device): m_device(device)
	{
		m_descriptor_pool = std::make_unique<DescriptorPool>(m_device);
	}

	BindingManager::~BindingManager()
	{
	}

}