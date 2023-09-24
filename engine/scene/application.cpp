#include "application.h"

namespace ToolEngine
{
	Application::Application()
	{
		Timer::Start();
		Window::Properties properties;
		properties.title = "Tool Engine";
		properties.extent = { 1280, 720 };
		m_window = std::make_unique<GlfwWindow>(properties);
		m_render = std::make_unique<Render>(*m_window);
		
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
			OPTICK_FRAME("MainThread");
			Timer::Tick();
			m_window->processEvents();
			m_render->drawFrame();
		}
		return ExitCode::Failed;
	}

	ExitCode Application::cleanup()
	{
		return ExitCode();
	}
}