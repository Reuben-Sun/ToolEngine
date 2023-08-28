#include "include/rhi/descriptor_sets.h"

namespace ToolEngine
{
    DescriptorSets::DescriptorSets(Device& device, DescriptorSetLayout& descriptor_set_layout, DescriptorPool& descriptor_pool, uint32_t frames_in_flight_count)
        : m_device(device), m_descriptor_set_layout(descriptor_set_layout), m_descriptor_pool(descriptor_pool), m_frames_in_flight_count(frames_in_flight_count)
    {
        std::vector<VkDescriptorSetLayout> layouts(m_frames_in_flight_count, m_descriptor_set_layout.getHandle());
        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = m_descriptor_pool.getHandle();
        allocInfo.descriptorSetCount = static_cast<uint32_t>(m_frames_in_flight_count);
        allocInfo.pSetLayouts = layouts.data();

        m_descriptor_sets.resize(m_frames_in_flight_count);
        if (vkAllocateDescriptorSets(m_device.getHandle(), &allocInfo, m_descriptor_sets.data()) != VK_SUCCESS) 
        {
            throw std::runtime_error("failed to allocate descriptor sets!");
        }

        /*for (size_t i = 0; i < m_frames_in_flight_count; i++) 
        {
            VkDescriptorBufferInfo bufferInfo{};
            bufferInfo.buffer = uniformBuffers[i];
            bufferInfo.offset = 0;
            bufferInfo.range = sizeof(UniformBufferObject);

            VkWriteDescriptorSet descriptorWrite{};
            descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrite.dstSet = m_descriptor_sets[i];
            descriptorWrite.dstBinding = 0;
            descriptorWrite.dstArrayElement = 0;
            descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            descriptorWrite.descriptorCount = 1;
            descriptorWrite.pBufferInfo = &bufferInfo;

            vkUpdateDescriptorSets(m_device.getHandle(), 1, &descriptorWrite, 0, nullptr);
        }*/
    }
    DescriptorSets::~DescriptorSets()
    {
    }
}