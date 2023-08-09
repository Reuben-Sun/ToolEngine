#pragma once

#include <memory>
#include "glfw_window.h"
#include "include/rhi/instance.h"

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
		// TODO: Timer
		// scene, device, rendercontext, pipeline...
	};
}