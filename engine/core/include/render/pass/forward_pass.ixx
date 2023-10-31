#include <vulkan/vulkan.h>
#include "include/rhi/device.h"

export module ForwardPass;
import RenderPass;
import PhysicalDevice;

namespace ToolEngine
{
	export class ForwardPass : public RenderPass
	{
	public:
		ForwardPass(Device& device, PhysicalDevice& physical_device, VkFormat format);
		~ForwardPass();
	};
}