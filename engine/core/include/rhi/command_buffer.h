#pragma once

#include <vulkan/vulkan.h>
#include <stdexcept>
#include "device.h"

namespace ToolEngine
{
	class CommandBuffer
	{
	public:
		CommandBuffer(Device& device);
		~CommandBuffer();

		VkCommandBuffer getHandle() const { return m_command_buffer; }
	private:
		VkCommandBuffer m_command_buffer;
		Device& m_device;
	};
}