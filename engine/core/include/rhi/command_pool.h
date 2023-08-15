#pragma once

#include <vulkan/vulkan.h>
#include <stdexcept>

namespace ToolEngine
{
	class CommandPool
	{
	public:
		CommandPool(VkDevice& device, uint32_t queue_family_index);
		~CommandPool();

		VkCommandPool getHandle() const { return m_command_pool; }

	private:
		VkCommandPool m_command_pool;
		VkDevice& m_device;
	};
}