#include "include/common/macro.h"

export module DescriptorSetLayout;
import PipelineLayout;
import Device;

namespace ToolEngine
{
	export class DescriptorSetLayout
	{
	public:
		DescriptorSetLayout(Device& device, uint32_t binding_index);
		~DescriptorSetLayout();

		VkDescriptorSetLayout getHandle() const { return m_descriptor_set_layout; }
		uint32_t getBindingIndex() const { return m_binding_index; }
	private:
		VkDescriptorSetLayout m_descriptor_set_layout{ VK_NULL_HANDLE };
		Device& m_device;
		uint32_t m_binding_index;
	};
}