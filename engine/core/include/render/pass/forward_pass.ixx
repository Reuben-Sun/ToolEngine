#include "include/common/macro.h"

export module ForwardPass;
import RenderPass;
import PhysicalDevice;
import Device;

namespace ToolEngine
{
	export class ForwardPass : public RenderPass
	{
	public:
		ForwardPass(Device& device, PhysicalDevice& physical_device, VkFormat format);
		~ForwardPass();
	};
}