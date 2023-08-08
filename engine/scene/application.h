#pragma once

#include <memory>
#include "glfw_window.h"

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
		// TODO: Timer
	};
}