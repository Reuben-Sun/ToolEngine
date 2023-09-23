#pragma once

#include <vulkan/vulkan.h>
#include <array>
#include "device.h"
#include "physical_device.h"
#include "include/common/depth_support_details.h"

namespace ToolEngine
{
	class RenderPass 
	{
	public:
		RenderPass(Device& device, PhysicalDevice& physical_device, VkFormat format);
		~RenderPass();

		VkRenderPass getHandle() const { return m_render_pass; }

	private:
		VkRenderPass m_render_pass;
		Device& m_device;
		PhysicalDevice& m_physical_device;
	};
}