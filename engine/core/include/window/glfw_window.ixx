#include "include/common/macro.h"
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

export module GLFW_Window;

import Window;
import GlobalContext;
import Instance;

namespace ToolEngine
{
	export class GlfwWindow: public Window
	{
	public:
		GlfwWindow(Window::Properties& properties);
		virtual ~GlfwWindow();

		VkSurfaceKHR createSurface(Instance& instance) override;
		bool shouldClose() override;
		void processEvents() override;
		std::vector<const char*> getRequiredSurfaceExtensions() const override;
        Window::Extent resize() override;
        Window::Properties getProperties() const { return m_properties; }

		static void onErrorCallback(int error_code, const char* description);
		static void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void onCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
		static bool m_dragging;
		static double m_last_x;
		static double m_last_y;
		static double m_drag_threshold;
	private:
		GLFWwindow* m_window = nullptr;
        Window::Properties& m_properties;
	};
}