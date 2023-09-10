#include "include/rhi/texture_image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "include/file/stb_image.h"

namespace ToolEngine
{
	TextureImage::TextureImage(Device& device, PhysicalDevice& physical_device): Buffer(device, physical_device)
	{
		int texWidth, texHeight, texChannels;
		std::string path = FileUtils::getRootPath() + "\\textures\\CalibrationFloorDiffuse.jpeg";
		stbi_uc* pixels = stbi_load(path.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
	}
	TextureImage::~TextureImage()
	{
	}
}