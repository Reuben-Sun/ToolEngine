#include "include/rhi/texture_image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "include/file/stb_image.h"

namespace ToolEngine
{
	TextureImage::TextureImage(Device& device, PhysicalDevice& physical_device, std::string file_path): Buffer(device, physical_device)
	{
		// stb load image
		int texture_width, texture_height, texture_channels;
		std::string path = FileUtils::getInstance().getImagePath() + file_path;
		stbi_uc* pixels = stbi_load(path.c_str(), &texture_width, &texture_height, &texture_channels, STBI_rgb_alpha);
		if (!pixels)
		{
			throw std::runtime_error("failed to load texture image!");
		}
		// create stage buffer
		VkDeviceSize image_buffer_size = texture_width * texture_height * 4;
		VkBuffer staging_buffer;
		VkDeviceMemory staging_buffer_memory;
		createBuffer(image_buffer_size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, staging_buffer, staging_buffer_memory);
		void* data;
		vkMapMemory(m_device.getHandle(), staging_buffer_memory, 0, image_buffer_size, 0, &data);
		memcpy(data, pixels, static_cast<size_t>(image_buffer_size));
		vkUnmapMemory(m_device.getHandle(), staging_buffer_memory);
		// stb unload image
		stbi_image_free(pixels);
		// create image
		VkExtent2D extent { texture_width, texture_height };
		m_texture_image = std::make_unique<Image>(m_device, m_physical_device, extent, VK_FORMAT_R8G8B8A8_SRGB,
			VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		// copy buffer to image
		transitionImageLayout(VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
		createImageFormBuffer(staging_buffer, static_cast<uint32_t>(texture_width), static_cast<uint32_t>(texture_height));
		transitionImageLayout(VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
		// destroy stage buffer
		vkDestroyBuffer(m_device.getHandle(), staging_buffer, nullptr);
		vkFreeMemory(m_device.getHandle(), staging_buffer_memory, nullptr);
	}
	TextureImage::~TextureImage()
	{
	}
	
	void TextureImage::transitionImageLayout(VkImageLayout old_layout, VkImageLayout new_layout)
	{
		std::unique_ptr<SingleTimeCommandBuffer> command_buffer = std::make_unique<SingleTimeCommandBuffer>(m_device);
		// use memory barrier to make sure image load before next operation, especially asynchronous programs
		VkImageMemoryBarrier barrier{};
		barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		barrier.oldLayout = old_layout;
		barrier.newLayout = new_layout;
		barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.image = m_texture_image->getHandle();
		barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		barrier.subresourceRange.baseMipLevel = 0;
		barrier.subresourceRange.levelCount = 1;
		barrier.subresourceRange.baseArrayLayer = 0;
		barrier.subresourceRange.layerCount = 1;

		VkPipelineStageFlags source_stage;
		VkPipelineStageFlags destination_stage;

		if (old_layout == VK_IMAGE_LAYOUT_UNDEFINED && new_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) 
		{
			barrier.srcAccessMask = 0;
			barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

			source_stage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			destination_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		}
		else if (old_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && new_layout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) 
		{
			barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

			source_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
			destination_stage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		}
		else 
		{
			throw std::invalid_argument("unsupported layout transition!");
		}

		vkCmdPipelineBarrier(command_buffer->getHandle(),
			source_stage, destination_stage,
			0,
			0, nullptr,
			0, nullptr,
			1, &barrier
		);

	}
	void TextureImage::createImageFormBuffer(VkBuffer buffer, uint32_t width, uint32_t height)
	{
		std::unique_ptr<SingleTimeCommandBuffer> command_buffer = std::make_unique<SingleTimeCommandBuffer>(m_device);
		VkBufferImageCopy region{};
		region.bufferOffset = 0;
		region.bufferRowLength = 0;
		region.bufferImageHeight = 0;
		region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		region.imageSubresource.mipLevel = 0;
		region.imageSubresource.baseArrayLayer = 0;
		region.imageSubresource.layerCount = 1;
		region.imageOffset = { 0, 0, 0 };
		region.imageExtent = { width, height, 1 };
		vkCmdCopyBufferToImage(command_buffer->getHandle(), buffer, m_texture_image->getHandle(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
	}
}