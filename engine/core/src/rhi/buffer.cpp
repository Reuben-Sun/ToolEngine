#include "include/rhi/buffer.h"

namespace ToolEngine
{
	Buffer::Buffer(Device& device, PhysicalDevice& physical_device)
		: m_device(device), m_physical_device(physical_device)
	{
	}

}