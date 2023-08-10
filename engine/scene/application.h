#pragma once

#include <memory>
#include "glfw_window.h"
#include "include/rhi/instance.h"
#include "include/rhi/physical_device.h"
#include "include/rhi/device.h"
#include "include/rhi/swapchain.h"
#include "include/rhi/image_view.h"

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
		// TODO: Timer
		// scene, device, rendercontext, pipeline...
	};
}