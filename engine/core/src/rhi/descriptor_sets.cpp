#include "include/rhi/descriptor_sets.h"

import UniformBuffer;
import DescriptorSetLayout;
import <array>;

namespace ToolEngine
{
    DescriptorSets::DescriptorSets(Device& device, DescriptorSetLayout& descriptor_set_layout, DescriptorPool& descriptor_pool, uint32_t frames_in_flight_count)
        : m_device(device), m_descriptor_set_layout(descriptor_set_layout), m_descriptor_pool(descriptor_pool), m_frames_in_flight_count(frames_in_flight_count)
    {
        std::vector<VkDescriptorSetLayout> layouts(m_frames_in_flight_count, m_descriptor_set_layout.getHandle());
        VkDescriptorSetAllocateInfo alloc_info{};
        alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        alloc_info.descriptorPool = m_descriptor_pool.getHandle();
        alloc_info.descriptorSetCount = static_cast<uint32_t>(m_frames_in_flight_count);
        alloc_info.pSetLayouts = layouts.data();

        m_descriptor_sets.resize(m_frames_in_flight_count);
        if (vkAllocateDescriptorSets(m_device.getHandle(), &alloc_info, m_descriptor_sets.data()) != VK_SUCCESS) 
        {
            throw std::runtime_error("failed to allocate descriptor sets!");
        }
    }
    DescriptorSets::~DescriptorSets()
    {
    }
    void DescriptorSets::updateDescriptorSets(VkBuffer ubo_buffer, VkImageView texture_image_view, VkSampler texture_sampler, uint32_t frames_in_flight_index)
    {
        VkDescriptorBufferInfo buffer_info{};
        buffer_info.buffer = ubo_buffer;
        buffer_info.offset = 0;
        buffer_info.range = sizeof(UniformBufferObject);

        VkDescriptorImageInfo image_info{};
        image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        image_info.imageView = texture_image_view;
        image_info.sampler = texture_sampler;

        std::array<VkWriteDescriptorSet, 2> descriptor_writes{};
        
        descriptor_writes[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptor_writes[0].dstSet = m_descriptor_sets[frames_in_flight_index];
        descriptor_writes[0].dstBinding = 0;
        descriptor_writes[0].dstArrayElement = 0;
        descriptor_writes[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptor_writes[0].descriptorCount = 1;
        descriptor_writes[0].pBufferInfo = &buffer_info;

        descriptor_writes[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptor_writes[1].dstSet = m_descriptor_sets[frames_in_flight_index];
        descriptor_writes[1].dstBinding = 1;
        descriptor_writes[1].dstArrayElement = 0;
        descriptor_writes[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        descriptor_writes[1].descriptorCount = 1;
        descriptor_writes[1].pImageInfo = &image_info;

        uint32_t descriptor_write_count = static_cast<uint32_t>(descriptor_writes.size());
        vkUpdateDescriptorSets(m_device.getHandle(), descriptor_write_count, descriptor_writes.data(), 0, nullptr);
    }
}