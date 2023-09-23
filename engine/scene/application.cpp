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
		m_instance = std::make_unique<Instance>(properties.title, m_window->getRequiredSurfaceExtensions());
		m_surface = m_window->createSurface(*m_instance);
		m_physical_device = std::make_unique<PhysicalDevice>(*m_instance, m_surface);
		m_device = std::make_unique<Device>(*m_instance, *m_physical_device, m_surface);
		VkExtent2D app_extent = { properties.extent.width, properties.extent.height };
		// create swap chain image resources
		m_swap_chain = std::make_unique<SwapChain>(*m_device, *m_physical_device, m_surface, app_extent);
		for (auto& image : m_swap_chain->getImages())
		{
			m_swap_chain_image_views.emplace_back(std::make_unique<ImageView>(*m_device, image, m_swap_chain->getFormat(), VK_IMAGE_ASPECT_COLOR_BIT));
		}
		// create depth resources
		m_depth_resources = std::make_unique<DepthResources>(*m_device, *m_physical_device, app_extent);
		// create pipeline
		m_blit_pipeline = std::make_unique<BlitPipeline>(*m_device, *m_physical_device, *m_swap_chain, MAX_FRAMES_IN_FLIGHT);
		for (auto& image_view : m_swap_chain_image_views)
		{
			m_frame_buffers.emplace_back(std::make_unique<FrameBuffer>(*m_device, m_blit_pipeline->getRenderPass().getHandle(), *image_view, app_extent.width, app_extent.height));
		}
		
		m_command_buffers = std::make_unique<CommandBuffer>(*m_device, MAX_FRAMES_IN_FLIGHT);
		
		// sync
		m_image_available_semaphores.resize(MAX_FRAMES_IN_FLIGHT);
		m_render_finished_semaphores.resize(MAX_FRAMES_IN_FLIGHT);
		m_in_flight_fences.resize(MAX_FRAMES_IN_FLIGHT);
		VkSemaphoreCreateInfo semaphore_info{};
		semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		VkFenceCreateInfo fence_info{};
		fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;
		for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i)
		{
			if (vkCreateSemaphore(m_device->getHandle(), &semaphore_info, nullptr, &m_image_available_semaphores[i]) != VK_SUCCESS ||
				vkCreateSemaphore(m_device->getHandle(), &semaphore_info, nullptr, &m_render_finished_semaphores[i]) != VK_SUCCESS ||
				vkCreateFence(m_device->getHandle(), &fence_info, nullptr, &m_in_flight_fences[i]) != VK_SUCCESS)
			{
				throw std::runtime_error("failed to create synchronization objects for a frame!");
			}
		}
		
	}

	Application::~Application()
	{
		if (m_surface != VK_NULL_HANDLE)
		{
			vkDestroySurfaceKHR(m_instance->getHandle(), m_surface, nullptr);
		}
		// sync
		for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i)
		{
			if (m_image_available_semaphores[i] != VK_NULL_HANDLE)
			{
				vkDestroySemaphore(m_device->getHandle(), m_image_available_semaphores[i], nullptr);
			}
			if (m_render_finished_semaphores[i] != VK_NULL_HANDLE)
			{
				vkDestroySemaphore(m_device->getHandle(), m_render_finished_semaphores[i], nullptr);
			}
			if (m_in_flight_fences[i] != VK_NULL_HANDLE)
			{
				vkDestroyFence(m_device->getHandle(), m_in_flight_fences[i], nullptr);
			}
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
			OPTICK_FRAME("MainThread");
			Timer::Tick();
			OPTICK_PUSH("process glfw events")
			m_window->processEvents();
			OPTICK_POP();
			drawFrame();
		}
		return ExitCode::Failed;
	}

	ExitCode Application::cleanup()
	{
		return ExitCode();
	}

	void Application::drawFrame()
	{
		OPTICK_TAG("FrameIndex", m_current_frame);
		OPTICK_EVENT();
		uint32_t current_frame_index = getModFrame();
		OPTICK_PUSH("wait for fence");
		vkWaitForFences(m_device->getHandle(), 1, &m_in_flight_fences[current_frame_index], VK_TRUE, UINT64_MAX);
		OPTICK_POP();

		OPTICK_PUSH("need next image");
		uint32_t image_index;
		VkResult result = vkAcquireNextImageKHR(m_device->getHandle(), m_swap_chain->getHandle(), UINT64_MAX, m_image_available_semaphores[current_frame_index], VK_NULL_HANDLE, &image_index);
		if (result == VK_ERROR_OUT_OF_DATE_KHR)
		{
			resizeFrame();
			return;
		}
		else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
		{
			throw std::runtime_error("failed to acquire swap chain image!");
		}
		OPTICK_POP();

		OPTICK_PUSH("reset fence");
		vkResetFences(m_device->getHandle(), 1, &m_in_flight_fences[current_frame_index]);
		OPTICK_POP();

		m_command_buffers->resetCommandBuffer(current_frame_index);
		
		// TODO: move this record to blit pipeline's renderTick()
		m_blit_pipeline->renderTick(*m_command_buffers, *m_frame_buffers[image_index], current_frame_index);
		
		// submit
		VkSemaphore wait_semaphores[] = { m_image_available_semaphores[current_frame_index]};
		VkSemaphore signal_semaphores[] = { m_render_finished_semaphores[current_frame_index]};
		m_command_buffers->submitCommandBuffer(current_frame_index, wait_semaphores, signal_semaphores, m_in_flight_fences[current_frame_index]);
		// present
		VkSwapchainKHR swap_chains[] = { m_swap_chain->getHandle() };
		m_device->present(signal_semaphores, image_index, swap_chains);

		++m_current_frame;
	}
	void Application::resizeFrame()
	{
		Window::Extent app_extent = m_window->resize();

		m_device->waitIdle();
		m_swap_chain = nullptr;
		for (int i = 0; i < m_frame_buffers.size(); ++i)
		{
			m_frame_buffers[i] = nullptr;
		}
		for (int i = 0; i < m_swap_chain_image_views.size(); ++i)
		{
			m_swap_chain_image_views[i] = nullptr;
		}
		
		m_swap_chain = std::make_unique<SwapChain>(*m_device, *m_physical_device, m_surface, VkExtent2D{ app_extent.width, app_extent.height });
		for (int i = 0; i < m_swap_chain_image_views.size(); ++i)
		{
			m_swap_chain_image_views[i] = std::make_unique<ImageView>(*m_device, m_swap_chain->getImages()[i], m_swap_chain->getFormat(), VK_IMAGE_ASPECT_COLOR_BIT);
		}
		m_blit_pipeline = std::make_unique<BlitPipeline>(*m_device, *m_physical_device, *m_swap_chain, MAX_FRAMES_IN_FLIGHT);
		for (int i = 0; i < m_frame_buffers.size(); ++i)
		{
			m_frame_buffers[i] = std::make_unique<FrameBuffer>(*m_device, m_blit_pipeline->getRenderPass().getHandle(), *m_swap_chain_image_views[i], app_extent.width, app_extent.height);
		}
		
	}
	
}