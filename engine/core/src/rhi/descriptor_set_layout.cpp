#include "include/rhi/descriptor_set_layout.h"

namespace ToolEngine
{
	DescriptorSetLayout::DescriptorSetLayout(Device& device): m_device(device)
	{
		VkDescriptorSetLayoutBinding ubo_layout_binding{};
		ubo_layout_binding.binding = 0;
		ubo_layout_binding.descriptorCount = 1;
		ubo_layout_binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		ubo_layout_binding.pImmutableSamplers = nullptr;
		ubo_layout_binding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
		VkDescriptorSetLayoutCreateInfo layout_info{};
		layout_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layout_info.bindingCount = 1;
		layout_info.pBindings = &ubo_layout_binding;
		if (vkCreateDescriptorSetLayout(m_device.getHandle(), &layout_info, nullptr, &m_descriptor_set_layout) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create descriptor set layout!");
		}
	}
	DescriptorSetLayout::~DescriptorSetLayout()
	{
		if (m_descriptor_set_layout != VK_NULL_HANDLE)
		{
			vkDestroyDescriptorSetLayout(m_device.getHandle(), m_descriptor_set_layout, nullptr);
		}

	}
}