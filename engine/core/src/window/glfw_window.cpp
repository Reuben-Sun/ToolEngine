#include "include/window/glfw_window.h"

namespace ToolEngine
{
    GlfwWindow::GlfwWindow(Properties& properties): Window(properties), m_properties(properties)
    {
        if (!glfwInit())
        {
            throw std::runtime_error("GLFW couldn't be initialized.");
        }
        glfwSetErrorCallback(onErrorCallback);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        m_window = glfwCreateWindow(m_properties.extent.width, m_properties.extent.height, m_properties.title.c_str(), nullptr, nullptr);
        glfwSetKeyCallback(m_window, onKeyCallback);
        glfwSetMouseButtonCallback(m_window, onMouseButtonCallback);
    }

    GlfwWindow::~GlfwWindow()
    {
        glfwTerminate();
    }

    VkSurfaceKHR GlfwWindow::createSurface(Instance& instance)
    {
        VkSurfaceKHR surface;
        if (glfwCreateWindowSurface(instance.getHandle(), m_window, nullptr, &surface) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to set up debug messenger!");
        }
        return surface;
    }

    bool GlfwWindow::shouldClose()
    {
        return false;
    }

    void GlfwWindow::processEvents()
    {
        glfwPollEvents();
    }

    std::vector<const char*> GlfwWindow::getRequiredSurfaceExtensions() const
    {
        uint32_t glfw_extension_count { 0 };
        const char** glfw_extensions { glfwGetRequiredInstanceExtensions(&glfw_extension_count) };
        return { glfw_extensions, glfw_extensions + glfw_extension_count };
    }

    GlfwWindow::Extent GlfwWindow::resize()
    {
        int width = 0, height = 0;
        glfwGetFramebufferSize(m_window, &width, &height);
        while (width == 0 || height == 0) 
        {
            glfwGetFramebufferSize(m_window, &width, &height);
            glfwWaitEvents();
        }
        m_properties.extent.width = width;
        m_properties.extent.height = height;
        return m_properties.extent;
    }

    void GlfwWindow::onErrorCallback(int error_code, const char* description)
    {
        std::cout << "GLFW Run Error" << std::endl;
    }
    void GlfwWindow::onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            if (key == GLFW_KEY_W)
            {
                g_global_context.input_manager->push(InputCommand{0, "Key W"});
            }
        }
    }
    void GlfwWindow::onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT)
        {
            if (action == GLFW_PRESS) 
            {
                g_global_context.input_manager->push(InputCommand{ 1, "Left Mouse Down" });
            }
            else if (action == GLFW_RELEASE) 
            {
                g_global_context.input_manager->push(InputCommand{ 1, "Left Mouse Up" });
            }
        }
    }
}



