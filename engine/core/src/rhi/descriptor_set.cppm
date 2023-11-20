#include "include/common/macro.h"

import DescriptorSet;
import UniformBuffer;
import DescriptorSetLayout;
import Device;
import TextureImage;
import Global_Context;

namespace ToolEngine
{
    DescriptorSet::DescriptorSet(Device& device, DescriptorSetLayout& descriptor_set_layout, UniformBuffer& ubo_buffer)
        : m_device(device), m_descriptor_set_layout(descriptor_set_layout)
    {
        VkDescriptorSetAllocateInfo alloc_info{};
        alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        alloc_info.descriptorPool = g_global_context.m_binding_manager->getDescriptorPool().getHandle();
        alloc_info.descriptorSetCount = 1;
        alloc_info.pSetLayouts = m_descriptor_set_layout.getHandlePtr();

        if (vkAllocateDescriptorSets(m_device.getHandle(), &alloc_info, &m_descriptor_set) != VK_SUCCESS) 
        {
            LOG_ERROR("failed to allocate descriptor sets!");
        }

        std::array<VkWriteDescriptorSet, 1> descriptor_writes{};
        descriptor_writes[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptor_writes[0].dstSet = m_descriptor_set;
        descriptor_writes[0].dstBinding = 0;
        descriptor_writes[0].dstArrayElement = 0;
        descriptor_writes[0].descriptorType = DescriptorTypeMap[DescriptorType::ConstantBuffer];
        descriptor_writes[0].descriptorCount = 1;
        descriptor_writes[0].pBufferInfo = ubo_buffer.getDescriptor();
        uint32_t descriptor_write_count = static_cast<uint32_t>(descriptor_writes.size());
        vkUpdateDescriptorSets(m_device.getHandle(), descriptor_write_count, descriptor_writes.data(), 0, nullptr);
    }
    DescriptorSet::~DescriptorSet()
    {
    }
}