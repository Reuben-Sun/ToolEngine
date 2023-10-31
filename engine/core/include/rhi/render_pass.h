#pragma once

#include <vulkan/vulkan.h>
#include <array>
#include "device.h"
#include "physical_device.h"

import DepthSupportDetails;

namespace ToolEngine
{
	class RenderPass 
	{
	public:
		RenderPass(Device& device, PhysicalDevice& physical_device, VkFormat format);
		virtual ~RenderPass();

		VkRenderPass getHandle() const { return m_render_pass; }

	protected:
		VkRenderPass m_render_pass;
		Device& m_device;
		PhysicalDevice& m_physical_device;
	};
}