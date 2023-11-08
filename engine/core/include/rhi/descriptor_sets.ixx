#include <vulkan/vulkan.h>

export module DescriptorSets;

import DescriptorPool;
import DescriptorSetLayout;
import Device;
import UniformBuffer;
import TextureImage;
import <vector>;

namespace ToolEngine
{
	export class DescriptorSets
	{
	public:
		DescriptorSets(Device& device, DescriptorSetLayout& descriptor_set_layout, DescriptorPool& descriptor_pool, UniformBuffer& ubo_buffer, TextureImage& texture_image);
		~DescriptorSets();
		VkDescriptorSet* getHandlePtr() { return &m_descriptor_set; }
	private:
		VkDescriptorSet m_descriptor_set;
		Device& m_device;
		DescriptorSetLayout& m_descriptor_set_layout;
		DescriptorPool& m_descriptor_pool;
	};
}