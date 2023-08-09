#pragma once

#include <vulkan/vulkan.h>
#include "instance.h"
#include "physical_device.h"
#include "include/common/queue_family_indices.h"

namespace ToolEngine
{
	class Device
	{
	public:
		Device(Instance& instance, PhysicalDevice& physical_device, VkSurfaceKHR& surface);
		~Device();

		VkDevice getHandle() const { return m_device; }

	private:
		VkDevice m_device;
	};
}