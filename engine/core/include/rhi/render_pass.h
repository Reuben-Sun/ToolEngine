#pragma once

#include <vulkan/vulkan.h>
#include "device.h"

namespace ToolEngine
{
	class RenderPass 
	{
	public:
		RenderPass(Device& device, VkFormat format);
		~RenderPass();

		VkRenderPass getHandle() const { return m_render_pass; }

	private:
		VkRenderPass m_render_pass;
		Device& m_device;
	};
}