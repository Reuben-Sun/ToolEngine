#include "include/common/macro.h"

import DescriptorSet;
import UniformBuffer;
import DescriptorSetLayout;
import Device;
import TextureImage;
import GlobalContext;
import DescriptorType;

namespace ToolEngine
{
    DescriptorSet::DescriptorSet(Device& device, DescriptorSetLayout& descriptor_set_layout, UniformBuffer& global_ubo_buffer, UniformBuffer& permesh_ubo_buffer)
        : m_device(device), m_descriptor_set_layout(descriptor_set_layout)
    {
        std::vector<VkDescriptorSetLayout> layouts = { m_descriptor_set_layout.getHandle() };
        VkDescriptorSetAllocateInfo alloc_info{};
        alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        alloc_info.descriptorPool = g_global_context.m_binding_manager->getDescriptorPool().getHandle();
        alloc_info.descriptorSetCount = 1;
        alloc_info.pSetLayouts = layouts.data();

        if (vkAllocateDescriptorSets(m_device.getHandle(), &alloc_info, &m_descriptor_set) != VK_SUCCESS) 
        {
            LOG_ERROR("failed to allocate descriptor sets!");
        }

        std::vector<VkWriteDescriptorSet> descriptor_writes;
        descriptor_writes.resize(2);
        descriptor_writes[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptor_writes[0].dstSet = m_descriptor_set;
        descriptor_writes[0].dstBinding = 0;
        descriptor_writes[0].dstArrayElement = 0;
        descriptor_writes[0].descriptorType = DescriptorTypeMap[DescriptorType::ConstantBuffer];
        descriptor_writes[0].descriptorCount = 1;
        descriptor_writes[0].pBufferInfo = global_ubo_buffer.getDescriptor();
        descriptor_writes[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptor_writes[1].dstSet = m_descriptor_set;
		descriptor_writes[1].dstBinding = 1;
        descriptor_writes[1].dstArrayElement = 0;
        descriptor_writes[1].descriptorType = DescriptorTypeMap[DescriptorType::DynamicBuffer];
        descriptor_writes[1].descriptorCount = 1;
        descriptor_writes[1].pBufferInfo = permesh_ubo_buffer.getDescriptor();


        uint32_t descriptor_write_count = static_cast<uint32_t>(descriptor_writes.size());
        vkUpdateDescriptorSets(m_device.getHandle(), descriptor_write_count, descriptor_writes.data(), 0, nullptr);
    }
    DescriptorSet::~DescriptorSet()
    {
    }
}