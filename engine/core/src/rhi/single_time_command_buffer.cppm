#include "include/common/macro.h"

import SingleTimeCommandBuffer;
import Device;

namespace ToolEngine
{
	SingleTimeCommandBuffer::SingleTimeCommandBuffer(Device& device): m_device(device)
	{
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = m_device.getCommandPool().getHandle();
        allocInfo.commandBufferCount = 1;

        vkAllocateCommandBuffers(m_device.getHandle(), &allocInfo, &m_command_buffer);

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(m_command_buffer, &beginInfo);
	}


	SingleTimeCommandBuffer::~SingleTimeCommandBuffer()
	{
        vkEndCommandBuffer(m_command_buffer);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &m_command_buffer;

        vkQueueSubmit(m_device.getGraphicsQueue().getHandle(), 1, &submitInfo, VK_NULL_HANDLE);
        vkQueueWaitIdle(m_device.getGraphicsQueue().getHandle());

        vkFreeCommandBuffers(m_device.getHandle(), m_device.getCommandPool().getHandle(), 1, &m_command_buffer);
	}
}