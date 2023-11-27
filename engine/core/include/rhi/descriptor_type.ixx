#include "include/common/macro.h"

export module DescriptorType;

namespace ToolEngine
{
	export enum class DescriptorType
	{
		Sampler,
		ConstantBuffer,
		DynamicBuffer
	};

	export std::unordered_map<DescriptorType, VkDescriptorType> DescriptorTypeMap =
	{
		{ DescriptorType::Sampler, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER },
		{ DescriptorType::ConstantBuffer, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER },
		{ DescriptorType::DynamicBuffer, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC }
	};
}