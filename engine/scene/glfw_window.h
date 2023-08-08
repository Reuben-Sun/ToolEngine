#pragma once

#include "window.h"

namespace ToolEngine
{
	class GLFWWindow: public Window
	{
	public:
		GLFWWindow(const Properties& properties);
		virtual ~GLFWWindow();

		VkSurfaceKHR createSurface(Instance& instance) override;
		bool shouldClose() override;
		void processEvents() override;
	private:
		GLFWWindow* m_window = nullptr;
	};
}