#include "application.h"

namespace ToolEngine
{
	Application::Application()
	{
		Window::Properties properties;
		properties.title = "Tool Engine";
		properties.extent = { 1280, 720 };
		m_window = std::make_unique<GlfwWindow>(properties);
		m_instance = std::make_unique<Instance>(properties.title, m_window->getRequiredSurfaceExtensions());
		m_surface = m_window->createSurface(*m_instance);
		m_physical_device = std::make_unique<PhysicalDevice>(*m_instance, m_surface);
	}
	Application::~Application()
	{
		if (m_surface != VK_NULL_HANDLE)
		{
			vkDestroySurfaceKHR(m_instance->getHandle(), m_surface, nullptr);
		}
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
			// TODO: draw frame
		}
		return ExitCode::Failed;
	}
}