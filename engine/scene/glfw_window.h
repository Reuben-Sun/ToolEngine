#pragma once

#include <iostream>
#include <string>
#include <vulkan/vulkan.h>
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"
#include "window.h"

namespace ToolEngine
{
	class GlfwWindow: public Window
	{
	public:
		GlfwWindow(const Properties& properties);
		virtual ~GlfwWindow();

		VkSurfaceKHR createSurface(Instance& instance) override;
		bool shouldClose() override;
		void processEvents() override;
		std::vector<const char*> getRequiredSurfaceExtensions() const override;

		static void onErrorCallback(int error_code, const char* description);
	private:
		GLFWwindow* m_window = nullptr;
	};
}