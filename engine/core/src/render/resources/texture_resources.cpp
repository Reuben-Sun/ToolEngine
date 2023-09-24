#include "include/render/resources/texture_resources.h"

namespace ToolEngine
{
	TextureResources::TextureResources(Device& device, PhysicalDevice& physical_device, VkExtent2D extent)
		: RenderResources(device, physical_device)
	{
		// TODO: move texture_image to there
	}
	TextureResources::~TextureResources()
	{
	}
}