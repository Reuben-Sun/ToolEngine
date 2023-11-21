#include "include/common/macro.h"

import DescriptorSetLayout;
import PipelineLayout;
import Device;
import DescriptorType;

namespace ToolEngine
{
	// TODO: convert a array, store binding info
	// binding info contain two prop, bind index and type(image or buffer)
	DescriptorSetLayout::DescriptorSetLayout(Device& device, uint32_t binding_index): m_device(device)
	{
		// ubo
		VkDescriptorSetLayoutBinding ubo_layout_binding{};
		ubo_layout_binding.binding = binding_index;
		ubo_layout_binding.descriptorCount = 1;
		ubo_layout_binding.descriptorType = DescriptorTypeMap[DescriptorType::ConstantBuffer];
		ubo_layout_binding.pImmutableSamplers = nullptr;
		ubo_layout_binding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
		
		// create info
		std::array<VkDescriptorSetLayoutBinding, 1> bindings = { ubo_layout_binding };
		VkDescriptorSetLayoutCreateInfo layout_info{};
		layout_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layout_info.bindingCount = static_cast<uint32_t>(bindings.size());
		layout_info.pBindings = bindings.data();

		if (vkCreateDescriptorSetLayout(m_device.getHandle(), &layout_info, nullptr, &m_descriptor_set_layout) != VK_SUCCESS)
		{
			LOG_ERROR("failed to create descriptor set layout!");
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