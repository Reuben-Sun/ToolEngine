#include "include/common/macro.h"

export module DescriptorSet;

import DescriptorPool;
import DescriptorSetLayout;
import Device;
import UniformBuffer;
import TextureImage;

namespace ToolEngine
{
	export class DescriptorSet
	{
	public:
		DescriptorSet(Device& device, DescriptorSetLayout& descriptor_set_layout, UniformBuffer& ubo_buffer);
		~DescriptorSet();
		VkDescriptorSet getHandle() { return m_descriptor_set; }
	private:
		VkDescriptorSet m_descriptor_set;
		Device& m_device;
		DescriptorSetLayout& m_descriptor_set_layout;
	};
}