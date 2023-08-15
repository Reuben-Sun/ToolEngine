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
		m_device = std::make_unique<Device>(*m_instance, *m_physical_device, m_surface);
		VkExtent2D app_extent = { properties.extent.width, properties.extent.height };
		m_swap_chain = std::make_unique<SwapChain>(*m_device, *m_physical_device, m_surface, app_extent);
		for (auto& image : m_swap_chain->getImages())
		{
			m_swap_chain_image_views.emplace_back(std::make_unique<ImageView>(*m_device, image, m_swap_chain->getFormat()));
		}
		m_blit_pipeline = std::make_unique<BlitPipeline>(*m_device, m_swap_chain->getFormat());
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