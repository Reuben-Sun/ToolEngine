#pragma once

#include <memory>
#include <optick.h>
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
#include "include/rhi/vertex_buffer.h"
#include "include/rhi/index_buffer.h"
#include "include/rhi/uniform_buffer.h"
#include "include/rhi/descriptor_pool.h"
#include "include/logic/timer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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

		const int MAX_FRAMES_IN_FLIGHT = 2;
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
		std::unique_ptr<CommandBuffer> m_command_buffers;
		std::unique_ptr<VertexBuffer> m_vertex_buffer;
		std::unique_ptr<IndexBuffer> m_index_buffer;
		std::vector<std::unique_ptr<UniformBuffer>> m_uniform_buffers;

		std::vector<VkSemaphore> m_image_available_semaphores;
		std::vector<VkSemaphore> m_render_finished_semaphores;
		std::vector<VkFence> m_in_flight_fences;

		// TODO: Timer, scene, rendercontext
		uint32_t m_current_frame = 0;
		void drawFrame();
		uint32_t getModFrame() { return m_current_frame % MAX_FRAMES_IN_FLIGHT; }
		void resizeFrame();
		void updateUniformBuffer(uint32_t current_image);
	};
}