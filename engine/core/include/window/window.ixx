#include <vulkan/vulkan.h>
#include "include/rhi/instance.h"

export module Window;

import <string>;


namespace ToolEngine
{
	export class Window
	{
	public:
		struct Extent 
		{
			uint32_t width;
			uint32_t height;
		};

		struct Properties
		{
			std::string title = "";
			Extent extent = { 1280, 720 };
		};

		Window(const Properties &properties);
		virtual ~Window() = default;
		virtual VkSurfaceKHR createSurface(Instance &instance) = 0;
		virtual bool shouldClose() = 0;
		virtual void processEvents() = 0;
		virtual std::vector<const char*> getRequiredSurfaceExtensions() const = 0;

		const Extent& getExtent() const { return m_properties.extent; }
		virtual Extent resize() = 0;
	protected:
		Properties m_properties;
	};

}