#include <array>
#include <vulkan/vulkan.h>
#include "include/rhi/device.h"
#include "include/rhi/pipeline_layout.h"
#include "include/common/macro.h"
import DescriptorSetLayout;

namespace ToolEngine
{
	DescriptorSetLayout::DescriptorSetLayout(Device& device): m_device(device)
	{
		// ubo
		VkDescriptorSetLayoutBinding ubo_layout_binding{};
		ubo_layout_binding.binding = 0;
		ubo_layout_binding.descriptorCount = 1;
		ubo_layout_binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		ubo_layout_binding.pImmutableSamplers = nullptr;
		ubo_layout_binding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
		// texture binding
		VkDescriptorSetLayoutBinding sampler_layout_binding{};
		sampler_layout_binding.binding = 1;
		sampler_layout_binding.descriptorCount = 1;
		sampler_layout_binding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		sampler_layout_binding.pImmutableSamplers = nullptr;
		sampler_layout_binding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
		// create info
		std::array<VkDescriptorSetLayoutBinding, 2> bindings = { ubo_layout_binding, sampler_layout_binding };
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