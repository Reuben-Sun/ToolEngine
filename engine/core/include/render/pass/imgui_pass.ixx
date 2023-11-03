export module ImguiPass;
import RenderPass;
import PhysicalDevice;
import Device;

namespace ToolEngine
{
	export class ImguiPass : RenderPass
	{
	public:
		ImguiPass(Device& device, PhysicalDevice& physical_device, VkFormat format);
		~ImguiPass();
	};
}