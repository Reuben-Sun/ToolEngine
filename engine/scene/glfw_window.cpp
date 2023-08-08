#include "glfw_window.h"

namespace ToolEngine
{
    VkSurfaceKHR GLFWWindow::createSurface(Instance& instance)
    {
        return VkSurfaceKHR();
    }

    bool GLFWWindow::shouldClose()
    {
        return false;
    }

    void GLFWWindow::processEvents()
    {
    }
}



