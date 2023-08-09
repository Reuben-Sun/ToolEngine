#pragma once

#include <memory>
#include "glfw_window.h"
#include "include/rhi/instance.h"
#include "include/rhi/physical_device.h"

namespace ToolEngine
{
	enum class ExitCode
	{
		Success = 0,
		Failed = 1
	};

	class Application
	{
	public:
		Application();
		~Application();

		ExitCode init();
		ExitCode mainLoop();
	private:
		std::unique_ptr<GlfwWindow> m_window;
		std::unique_ptr<Instance> m_instance;
		VkSurfaceKHR m_surface{ VK_NULL_HANDLE };
		std::unique_ptr<PhysicalDevice> m_physical_device;
		// TODO: Timer
		// scene, device, rendercontext, pipeline...
	};
}