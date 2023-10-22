#pragma once

#include <memory>
#include <optick.h>
#include "include/window/glfw_window.h"
#include "include/render/render.h"
#include "scene.h"

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
		ExitCode cleanup();

	private:
		std::unique_ptr<GlfwWindow> m_window;
		std::unique_ptr<Render> m_render;
		std::unique_ptr<Scene> m_scene;
	};
}