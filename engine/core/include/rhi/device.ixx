#include <vulkan/vulkan.h>
#include <optick.h>

export module Device;

import Queue;
import CommandPool;
import Instance;
import QueueFamilyIndices;
import PhysicalDevice;
import <memory>;

namespace ToolEngine
{
	export class Device
	{
	public:
		Device(Instance& instance, PhysicalDevice& physical_device, VkSurfaceKHR& surface);
		~Device();

		VkDevice getHandle() const { return m_device; }
		VkResult waitIdle() const { return vkDeviceWaitIdle(m_device); }
		CommandPool& getCommandPool() const { return *m_command_pool; }
		Queue& getGraphicsQueue() const;
		Queue& getPresentQueue() const;

		void present(VkSemaphore* wait_semaphores, uint32_t image_index, VkSwapchainKHR* swap_chains);
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