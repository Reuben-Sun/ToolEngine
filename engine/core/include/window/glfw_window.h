#pragma once

#include <iostream>
#include <string>
#include <vulkan/vulkan.h>
#include "include/global/global_context.h"
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"
#include "window.h"

namespace ToolEngine
{
	class GlfwWindow: public Window
	{
	public:
		GlfwWindow(Properties& properties);
		virtual ~GlfwWindow();

		VkSurfaceKHR createSurface(Instance& instance) override;
		bool shouldClose() override;
		void processEvents() override;
		std::vector<const char*> getRequiredSurfaceExtensions() const override;
		Extent resize() override;
		Properties getProperties() const { return m_properties; }

		static void onErrorCallback(int error_code, const char* description);
		static void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	private:
		GLFWwindow* m_window = nullptr;
		Properties& m_properties;
	};
}