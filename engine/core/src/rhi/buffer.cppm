#include <vulkan/vulkan.h>
#include "include/common/macro.h"
import Buffer;
import SingleTimeCommandBuffer;
import PhysicalDevice;
import Device;

namespace ToolEngine
{
	Buffer::Buffer(Device& device, PhysicalDevice& physical_device): m_device(device), m_physical_device(physical_device)
	{
	}
}