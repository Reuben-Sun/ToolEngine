#pragma once

#include <vulkan/vulkan.h>
#include "instance.h"
#include "physical_device.h"

namespace ToolEngine
{
	class Device
	{
	public:
		Device(Instance& instance, PhysicalDevice& physical_device);
		~Device();

		VkDevice getHandle() const { return m_device; }

	private:
		VkDevice m_device;
	};
}