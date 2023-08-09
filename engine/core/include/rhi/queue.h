#pragma once

#include <vulkan/vulkan.h>
#include "device.h"

namespace ToolEngine
{
	class Queue
	{
	public:
		Queue(Device& device);
		~Queue();
		
		VkQueue getHandle() const { return m_queue; }

	private:
		VkQueue m_queue{ VK_NULL_HANDLE };
		Device &m_device;
	};
}