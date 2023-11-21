#include "include/common/macro.h"

export module TextureImage;

import GlobalContext;
import Buffer;
import Image;
import SingleTimeCommandBuffer;
import PhysicalDevice;
import Device;
import ImageView;
import Sampler;
import <string>;
import <memory>;

namespace ToolEngine
{
	export class TextureImage
	{
	public:
		TextureImage(Device& device, PhysicalDevice& physical_device, std::string file_path);
		~TextureImage();
		VkImage getHandle() const { return m_texture_image->getHandle(); }
		VkFormat getFormat() const { return m_texture_image->getFormat(); }
		VkImageView getImageView() const { return m_texture_image_view->getHandle(); }
		VkSampler getSampler() const { return m_texture_sampler->getHandle(); }
		VkDescriptorImageInfo* getDescriptor()
		{
			return &m_descriptor;
		}
	private:
		std::unique_ptr<Image> m_texture_image;
		std::unique_ptr<ImageView> m_texture_image_view;
		std::unique_ptr<Sampler> m_texture_sampler;
		Device& m_device;
		PhysicalDevice& m_physical_device;
		VkDescriptorImageInfo m_descriptor;
		void createImageFormBuffer(VkBuffer buffer, uint32_t width, uint32_t height);
	};
}