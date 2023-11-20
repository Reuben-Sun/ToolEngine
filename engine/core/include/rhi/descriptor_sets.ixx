#include "include/common/macro.h"

export module DescriptorSets;

import DescriptorPool;
import DescriptorSetLayout;
import Device;
import UniformBuffer;
import TextureImage;

namespace ToolEngine
{
	export class DescriptorSets
	{
	public:
		DescriptorSets(Device& device, DescriptorSetLayout& descriptor_set_layout, DescriptorPool& descriptor_pool);
		~DescriptorSets();
		void updateDescriptorSets(UniformBuffer& ubo_buffer, TextureImage& texture_image);
		VkDescriptorSet* getHandlePtr() { return &m_descriptor_set; }
	private:
		VkDescriptorSet m_descriptor_set;
		Device& m_device;
		DescriptorSetLayout& m_descriptor_set_layout;
		DescriptorPool& m_descriptor_pool;
	};
}