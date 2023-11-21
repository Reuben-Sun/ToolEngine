#include "include/common/macro.h"

export module DescriptorType;

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
}