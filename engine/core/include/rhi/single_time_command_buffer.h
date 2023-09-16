#pragma once 

#include <vulkan/vulkan.h>
#include "device.h"

namespace ToolEngine
{
	/// <summary>
	/// A buffer to execute a one-time command, such as submit texture
	/// </summary>
	class SingleTimeCommandBuffer
	{
	public:
		SingleTimeCommandBuffer(Device& device);
		~SingleTimeCommandBuffer();

		VkCommandBuffer getHandle() const { return m_command_buffer; }

	private:
		Device& m_device;
		VkCommandBuffer m_command_buffer;
	};
}