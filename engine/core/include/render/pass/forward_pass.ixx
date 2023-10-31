#include <vulkan/vulkan.h>
#include "include/rhi/device.h"
#include "include/rhi/physical_device.h"

export module ForwardPass;
import RenderPass;

namespace ToolEngine
{
	export class ForwardPass : public RenderPass
	{
	public:
		ForwardPass(Device& device, PhysicalDevice& physical_device, VkFormat format);
		~ForwardPass();
	};
}