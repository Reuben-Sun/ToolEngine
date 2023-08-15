#include "include/rhi/command_buffer.h"

namespace ToolEngine
{
	CommandBuffer::CommandBuffer(Device& device): m_device(device)
	{
		VkCommandBufferAllocateInfo alloc_info{};
		alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		alloc_info.commandPool = m_device.getCommandPool().getHandle();
		alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		alloc_info.commandBufferCount = 1;

		if (vkAllocateCommandBuffers(m_device.getHandle(), &alloc_info, &m_command_buffer) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to allocate command buffers!");
		}
	}
	CommandBuffer::~CommandBuffer()
	{
	}
}