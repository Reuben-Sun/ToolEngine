#pragma once

#include <vulkan/vulkan.h>
#include "include/rhi/device.h"
#include "include/rhi/physical_device.h"
#include "include/rhi/render_pass.h"

namespace ToolEngine
{
	class ForwardPass : public RenderPass
	{
	public:
		ForwardPass(Device& device, PhysicalDevice& physical_device, VkFormat format);
		~ForwardPass();
	};
}