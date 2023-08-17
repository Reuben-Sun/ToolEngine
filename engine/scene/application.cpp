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
		for (auto& image_view : m_swap_chain_image_views)
		{
			m_frame_buffers.emplace_back(std::make_unique<FrameBuffer>(*m_device, m_blit_pipeline->getRenderPass().getHandle(), *image_view, app_extent.width, app_extent.height));
		}
		m_command_buffer = std::make_unique<CommandBuffer>(*m_device);
		
		// sync
		VkSemaphoreCreateInfo semaphore_info{};
		semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		VkFenceCreateInfo fence_info{};
		fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;
		if (vkCreateSemaphore(m_device->getHandle(), &semaphore_info, nullptr, &m_image_available_semaphore) != VK_SUCCESS ||
			vkCreateSemaphore(m_device->getHandle(), &semaphore_info, nullptr, &m_render_finished_semaphore) != VK_SUCCESS ||
			vkCreateFence(m_device->getHandle(), &fence_info, nullptr, &m_in_flight_fence) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create synchronization objects for a frame!");
		}
	}

	Application::~Application()
	{
		if (m_surface != VK_NULL_HANDLE)
		{
			vkDestroySurfaceKHR(m_instance->getHandle(), m_surface, nullptr);
		}
		// sync
		if (m_image_available_semaphore != VK_NULL_HANDLE)
		{
			vkDestroySemaphore(m_device->getHandle(), m_image_available_semaphore, nullptr);
		}
		if (m_render_finished_semaphore != VK_NULL_HANDLE)
		{
			vkDestroySemaphore(m_device->getHandle(), m_render_finished_semaphore, nullptr);
		}
		if (m_in_flight_fence != VK_NULL_HANDLE)
		{
			vkDestroyFence(m_device->getHandle(), m_in_flight_fence, nullptr);
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
		OPTICK_EVENT();

		OPTICK_PUSH("wait for fence");
		vkWaitForFences(m_device->getHandle(), 1, &m_in_flight_fence, VK_TRUE, UINT64_MAX);
		OPTICK_POP();

		OPTICK_PUSH("reset fence");
		vkResetFences(m_device->getHandle(), 1, &m_in_flight_fence);
		OPTICK_POP();
		OPTICK_PUSH("need next image");
		uint32_t image_index;
		vkAcquireNextImageKHR(m_device->getHandle(), m_swap_chain->getHandle(), UINT64_MAX, m_image_available_semaphore, VK_NULL_HANDLE, &image_index);
		OPTICK_POP();

		m_command_buffer->resetCommandBuffer();
		// record
		m_command_buffer->beginRecord();

		VkRenderPassBeginInfo render_pass_info{};
		render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		render_pass_info.renderPass = m_blit_pipeline->getRenderPass().getHandle();
		render_pass_info.framebuffer = m_frame_buffers[image_index]->getHandle();
		render_pass_info.renderArea.offset = { 0, 0 };
		render_pass_info.renderArea.extent = m_swap_chain->getExtent();
		VkClearValue clear_color = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
		render_pass_info.clearValueCount = 1;
		render_pass_info.pClearValues = &clear_color;
		m_command_buffer->beginRenderPass(render_pass_info);

		m_command_buffer->bindPipeline(m_blit_pipeline->getPipeline().getHandle());

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = (float)m_swap_chain->getExtent().width;
		viewport.height = (float)m_swap_chain->getExtent().height;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		m_command_buffer->setViewport(viewport, 0, 1);

		VkRect2D scissor{};
		scissor.offset = { 0, 0 };
		scissor.extent = m_swap_chain->getExtent();
		m_command_buffer->setScissor(scissor, 0, 1);
		uint32_t vertex_count = 3;
		OPTICK_TAG("VertexCount", vertex_count);
		m_command_buffer->draw(vertex_count, 1, 0, 0);

		m_command_buffer->endRenderPass();

		m_command_buffer->endRecord();
		// submit
		VkSemaphore wait_semaphores[] = { m_image_available_semaphore };
		VkSemaphore signal_semaphores[] = { m_render_finished_semaphore };
		m_command_buffer->submitCommandBuffer(wait_semaphores, signal_semaphores, m_in_flight_fence);
		// present
		VkSwapchainKHR swap_chains[] = { m_swap_chain->getHandle() };
		m_device->present(signal_semaphores, image_index, swap_chains);
	}
}