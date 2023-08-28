#include "include/rhi/descriptor_sets.h"

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
    void DescriptorSets::updateDescriptorSets(VkBuffer buffer, uint32_t frames_in_flight_index)
    {
        VkDescriptorBufferInfo buffer_info{};
        buffer_info.buffer = buffer;
        buffer_info.offset = 0;
        buffer_info.range = sizeof(UniformBufferObject);

        VkWriteDescriptorSet descriptor_write{};
        descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptor_write.dstSet = m_descriptor_sets[frames_in_flight_index];
        descriptor_write.dstBinding = 0;
        descriptor_write.dstArrayElement = 0;
        descriptor_write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptor_write.descriptorCount = 1;
        descriptor_write.pBufferInfo = &buffer_info;

        vkUpdateDescriptorSets(m_device.getHandle(), 1, &descriptor_write, 0, nullptr);
    }
}