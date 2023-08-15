#pragma once

#include <memory>
#include "glfw_window.h"
#include "include/rhi/instance.h"
#include "include/rhi/physical_device.h"
#include "include/rhi/device.h"
#include "include/rhi/swapchain.h"
#include "include/rhi/image_view.h"
#include "include/rhi/render_pass.h"
#include "include/render/blit_pipeline.h"
#include "include/rhi/frame_buffer.h"
#include "include/rhi/command_buffer.h"

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
		VkSurfaceKHR m_surface{ VK_NULL_HANDLE };
		std::unique_ptr<PhysicalDevice> m_physical_device;
		std::unique_ptr<Device> m_device;
		std::unique_ptr<SwapChain> m_swap_chain;
		std::vector<std::unique_ptr<ImageView>> m_swap_chain_image_views;
		std::unique_ptr<BlitPipeline> m_blit_pipeline;
		std::vector<std::unique_ptr<FrameBuffer>> m_frame_buffers;
		std::unique_ptr<CommandBuffer> m_command_buffer;

		VkSemaphore m_image_available_semaphore;
		VkSemaphore m_render_finished_semaphore;
		VkFence m_in_flight_fence;
		// TODO: Timer, scene, rendercontext

		void drawFrame();
	};
}