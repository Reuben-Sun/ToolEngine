#pragma once

#include <string>
#include <vulkan/vulkan.h>
#include "include/rhi/instance.h"

namespace ToolEngine
{
	class Window
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

		const Extent& getExtent() const { return m_properties.extent; }
		Extent resize(const Extent& extent);
	protected:
		Properties m_properties;
	};

}