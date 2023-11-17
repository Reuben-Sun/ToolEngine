#include "include/common/macro.h"

export module Buffer;

import Vertex;
import SingleTimeCommandBuffer;
import PhysicalDevice;
import Device;

namespace ToolEngine
{
	export class Buffer
	{
	public:
		Buffer(Device& device, PhysicalDevice& physical_device);
		virtual ~Buffer() = default;

	protected:
		Device& m_device;
		PhysicalDevice& m_physical_device;
	};
}