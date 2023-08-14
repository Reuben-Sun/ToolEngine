#pragma once

#include <vulkan/vulkan.h>
#include "instance.h"
#include "physical_device.h"
#include "queue.h"
#include "include/common/queue_family_indices.h"

namespace ToolEngine
{
	class Queue;	// circular reference, need a pre-declaration

	class Device
	{
	public:
		Device(Instance& instance, PhysicalDevice& physical_device, VkSurfaceKHR& surface);
		~Device();

		VkDevice getHandle() const { return m_device; }

	private:
		VkDevice m_device;
		std::unique_ptr<Queue> m_graphics_queue;
		std::unique_ptr<Queue> m_present_queue;
	};
}