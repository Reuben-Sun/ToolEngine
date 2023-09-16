#include "include/rhi/texture_image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "include/file/stb_image.h"

namespace ToolEngine
{
	TextureImage::TextureImage(Device& device, PhysicalDevice& physical_device): Buffer(device, physical_device)
	{
		// stb load image
		int texture_width, texture_height, texture_channels;
		std::string path = FileUtils::getRootPath() + "\\textures\\CalibrationFloorDiffuse.jpeg";
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
		createImage(texture_width, texture_height, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);


	}
	TextureImage::~TextureImage()
	{
	}
	void TextureImage::createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties)
	{
		VkImageCreateInfo image_create_info{};
		image_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		image_create_info.imageType = VK_IMAGE_TYPE_2D;
		image_create_info.extent.width = width;
		image_create_info.extent.height = height;
		image_create_info.extent.depth = 1;
		image_create_info.mipLevels = 1;
		image_create_info.arrayLayers = 1;
		image_create_info.format = format;
		image_create_info.tiling = tiling;
		image_create_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		image_create_info.usage = usage;
		image_create_info.samples = VK_SAMPLE_COUNT_1_BIT;
		image_create_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateImage(m_device.getHandle(), &image_create_info, nullptr, &m_texture_image) != VK_SUCCESS) 
		{
			throw std::runtime_error("failed to create image!");
		}

		VkMemoryRequirements mem_requirements;
		vkGetImageMemoryRequirements(m_device.getHandle(), m_texture_image, &mem_requirements);

		VkMemoryAllocateInfo alloc_info{};
		alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		alloc_info.allocationSize = mem_requirements.size;
		alloc_info.memoryTypeIndex = findMemoryType(mem_requirements.memoryTypeBits, properties);

		if (vkAllocateMemory(m_device.getHandle(), &alloc_info, nullptr, &m_texture_image_memory) != VK_SUCCESS) 
		{
			throw std::runtime_error("failed to allocate image memory!");
		}

		vkBindImageMemory(m_device.getHandle(), m_texture_image, m_texture_image_memory, 0);
	}
}