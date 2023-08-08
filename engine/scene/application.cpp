#include "application.h"

namespace ToolEngine
{
	Application::Application()
	{
		Window::Properties properties;
		properties.title = "Tool Engine";
		properties.extent = { 1280, 720 };
		m_window = new GlfwWindow(properties);
	}
	Application::~Application()
	{
	}

	ExitCode Application::init()
	{
		return ExitCode();
	}
	ExitCode Application::mainLoop()
	{
		while (!m_window->shouldClose()) 
		{
			m_window->processEvents();
		}
		return ExitCode::Failed;
	}
}