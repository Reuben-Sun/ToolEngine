#pragma once

#include <memory>
#include <optick.h>
#include "include/common/macro.h"

import Timer;
import GLFW_Window;
import Global_Context;
import Render;
import Scene;

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

		ExitCode init(int argc, char* argv[]);
		ExitCode mainLoop();
		ExitCode cleanup();

	private:
		std::unique_ptr<GlfwWindow> m_window;
		std::unique_ptr<Render> m_render;
		std::unique_ptr<Scene> m_scene;
	};
}