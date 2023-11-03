import ImguiPass;

namespace ToolEngine
{
	ImguiPass::ImguiPass(Device& device, PhysicalDevice& physical_device, VkFormat format)
		: RenderPass(device, physical_device, format)
	{
	}
	ImguiPass::~ImguiPass()
	{
	}
}