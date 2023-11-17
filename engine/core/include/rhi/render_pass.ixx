#include "include/common/macro.h"

export module RenderPass;

import DepthSupportDetails;
import PhysicalDevice;
import Device;

namespace ToolEngine
{
	export class RenderPass 
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