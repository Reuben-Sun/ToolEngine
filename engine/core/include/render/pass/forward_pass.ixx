#include <vulkan/vulkan.h>
#include "include/rhi/device.h"
#include "include/rhi/physical_device.h"
#include "include/rhi/render_pass.h"

export module ForwardPass;

namespace ToolEngine
{
	export class ForwardPass : public RenderPass
	{
	public:
		ForwardPass(Device& device, PhysicalDevice& physical_device, VkFormat format);
		~ForwardPass();
	};
}