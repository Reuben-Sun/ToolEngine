#pragma once

#include <string>
#include <vulkan/vulkan.h>

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
		virtual VkSurfaceKHR createSurface() = 0;

	protected:
		Properties m_properties;
	};

}