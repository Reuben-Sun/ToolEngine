#include <vulkan/vulkan.h>
#include "include/rhi/device.h"
#include "include/rhi/physical_device.h"
#include "include/rhi/image.h"
#include "include/rhi/image_view.h"

export module RenderResources;

namespace ToolEngine
{
	export class RenderResources
	{
	public:
		RenderResources(Device& device, PhysicalDevice& physical_device);
		virtual ~RenderResources();
		ImageView& getImageView() { return *m_image_view; }

	protected:
		std::unique_ptr<Image> m_image;
		std::unique_ptr<ImageView> m_image_view;
		Device& m_device;
		PhysicalDevice& m_physical_device;
	};
}