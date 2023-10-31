#include <vulkan/vulkan.h>

export module DescriptorSetLayout;
import PipelineLayout;
import Device;

namespace ToolEngine
{
	export class DescriptorSetLayout
	{
	public:
		DescriptorSetLayout(Device& device);
		~DescriptorSetLayout();

		VkDescriptorSetLayout getHandle() const { return m_descriptor_set_layout; }
		const VkDescriptorSetLayout* getHandlePtr() { return &m_descriptor_set_layout; }
	private:
		VkDescriptorSetLayout m_descriptor_set_layout{ VK_NULL_HANDLE };
		Device& m_device;
	};
}