#include "include/common/macro.h"

export module DescriptorSet;

import DescriptorPool;
import DescriptorSetLayout;
import Device;
import UniformBuffer;
import TextureImage;

namespace ToolEngine
{
	export enum class DescriptorType
	{
		Sampler,
		TextureSRV,
		TextureUAV,
		ConstantBuffer,
		StructuredBuffer
	};

	export std::unordered_map<DescriptorType, VkDescriptorType> DescriptorTypeMap =
	{
		{ DescriptorType::Sampler, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER },
		{ DescriptorType::TextureSRV, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE },
		{ DescriptorType::TextureUAV, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE },
		{ DescriptorType::ConstantBuffer, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER },
		{ DescriptorType::StructuredBuffer, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER }
	};

	export class DescriptorSet
	{
	public:
		DescriptorSet(Device& device, DescriptorSetLayout& descriptor_set_layout, DescriptorPool& descriptor_pool);
		~DescriptorSet();
		void updateDescriptorSets(UniformBuffer& ubo_buffer, TextureImage& texture_image);
		VkDescriptorSet getHandle() { return m_descriptor_set; }
	private:
		VkDescriptorSet m_descriptor_set;
		Device& m_device;
		DescriptorSetLayout& m_descriptor_set_layout;
		DescriptorPool& m_descriptor_pool;
	};
}