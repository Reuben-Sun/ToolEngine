#pragma once

#include <vulkan/vulkan.h>
#include "instance.h"
#include "physical_device.h"
#include "queue.h"
#include "include/common/queue_family_indices.h"
#include "include/rhi/command_pool.h"

namespace ToolEngine
{
	class Queue;	// circular reference, need a pre-declaration

	class Device
	{
	public:
		Device(Instance& instance, PhysicalDevice& physical_device, VkSurfaceKHR& surface);
		~Device();

		VkDevice getHandle() const { return m_device; }
		VkResult waitIdle() const { return vkDeviceWaitIdle(m_device); }
		// request fence from fence pool
		// request command buffer from command pool

	private:
		VkDevice m_device;
		std::unique_ptr<Queue> m_graphics_queue;
		std::unique_ptr<Queue> m_present_queue;
		std::unique_ptr<CommandPool> m_command_pool;
		// fence pool
	};
}