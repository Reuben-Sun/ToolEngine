#include "include/common/macro.h"

import DescriptorSets;
import UniformBuffer;
import DescriptorSetLayout;
import Device;
import TextureImage;

namespace ToolEngine
{
    DescriptorSets::DescriptorSets(Device& device, DescriptorSetLayout& descriptor_set_layout, DescriptorPool& descriptor_pool)
        : m_device(device), m_descriptor_set_layout(descriptor_set_layout), m_descriptor_pool(descriptor_pool)
    {
        VkDescriptorSetAllocateInfo alloc_info{};
        alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        alloc_info.descriptorPool = m_descriptor_pool.getHandle();
        alloc_info.descriptorSetCount = 1;
        alloc_info.pSetLayouts = m_descriptor_set_layout.getHandlePtr();

        if (vkAllocateDescriptorSets(m_device.getHandle(), &alloc_info, &m_descriptor_set) != VK_SUCCESS) 
        {
            LOG_ERROR("failed to allocate descriptor sets!");
        }
    }
    DescriptorSets::~DescriptorSets()
    {
    }
    void DescriptorSets::updateDescriptorSets(UniformBuffer& ubo_buffer, TextureImage& texture_image)
    {
        std::array<VkWriteDescriptorSet, 2> descriptor_writes{};
        
        descriptor_writes[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptor_writes[0].dstSet = m_descriptor_set;
        descriptor_writes[0].dstBinding = 0;
        descriptor_writes[0].dstArrayElement = 0;
        descriptor_writes[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptor_writes[0].descriptorCount = 1;
        descriptor_writes[0].pBufferInfo = ubo_buffer.getDescriptor();

        descriptor_writes[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptor_writes[1].dstSet = m_descriptor_set;
        descriptor_writes[1].dstBinding = 1;
        descriptor_writes[1].dstArrayElement = 0;
        descriptor_writes[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        descriptor_writes[1].descriptorCount = 1;
        descriptor_writes[1].pImageInfo = texture_image.getDescriptor();

        uint32_t descriptor_write_count = static_cast<uint32_t>(descriptor_writes.size());
        vkUpdateDescriptorSets(m_device.getHandle(), descriptor_write_count, descriptor_writes.data(), 0, nullptr);
    }
}