#pragma once

#include <vulkan/vulkan.h>
#include "device.h"
#include "physical_device.h"
#include "vertex_descriptor.h"

namespace ToolEngine
{
	class Buffer
	{
	public:
		Buffer(Device& device, PhysicalDevice& physical_device);
		virtual ~Buffer() = default;

		VkBuffer getHandle() const { return m_buffer; }
	protected:
		VkBuffer m_buffer;
		VkDeviceMemory m_memory;
		Device& m_device;
		PhysicalDevice& m_physical_device;
		
	};
}