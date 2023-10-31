#include <vulkan/vulkan.h>

import RenderPass;
import Device;
import DepthSupportDetails;
import PhysicalDevice;
import <array>;

namespace ToolEngine
{
	RenderPass::RenderPass(Device& device, PhysicalDevice& physical_device, VkFormat format):
        m_device(device), m_physical_device(physical_device)
	{
	}

	RenderPass::~RenderPass()
	{
        if (m_render_pass != VK_NULL_HANDLE)
        {
			vkDestroyRenderPass(m_device.getHandle(), m_render_pass, nullptr);
		}
	}
}