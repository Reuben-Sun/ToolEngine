#include "include/common/macro.h"
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

import GLFW_Window;
import Global_Context;
import Instance;
import InputManager;

namespace ToolEngine
{
    bool GlfwWindow::m_dragging = false;
    double GlfwWindow::m_last_x = 0.0;
    double GlfwWindow::m_last_y = 0.0;
    double GlfwWindow::m_drag_threshold = 0.00001;

    GlfwWindow::GlfwWindow(Window::Properties& properties): Window(properties), m_properties(properties)
    {
        if (!glfwInit())
        {
            LOG_ERROR("GLFW couldn't be initialized.");
        }
        glfwSetErrorCallback(onErrorCallback);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        m_window = glfwCreateWindow(m_properties.extent.width, m_properties.extent.height, m_properties.title.c_str(), nullptr, nullptr);
        glfwSetKeyCallback(m_window, onKeyCallback);
        glfwSetMouseButtonCallback(m_window, onMouseButtonCallback);
        glfwSetCursorPosCallback(m_window, onCursorPosCallback);
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
            LOG_ERROR("failed to create window surface!");
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
        std::vector<const char*> extensions(glfw_extensions, glfw_extensions + glfw_extension_count);
        //const char* enabledExtensions[] = { VK_EXT_DEBUG_UTILS_EXTENSION_NAME };
        return extensions;
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
        LOG_ERROR("GLFW Run Error");
    }
    void GlfwWindow::onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            if (key == GLFW_KEY_W)
            {
                g_global_context.m_input_manager->push(InputCommand{ CommandType::MOVE, "Key W"});
            }
            else if (key == GLFW_KEY_S)
            {
				g_global_context.m_input_manager->push(InputCommand{ CommandType::MOVE, "Key S" });
			}
            else if (key == GLFW_KEY_A)
            {
				g_global_context.m_input_manager->push(InputCommand{ CommandType::MOVE, "Key A" });
			}
            else if (key == GLFW_KEY_D)
            {
				g_global_context.m_input_manager->push(InputCommand{ CommandType::MOVE, "Key D" });
			}
            else if (key == GLFW_KEY_Q)
            {
				g_global_context.m_input_manager->push(InputCommand{ CommandType::MOVE, "Key Q" });
			}
            else if (key == GLFW_KEY_E)
            {
				g_global_context.m_input_manager->push(InputCommand{ CommandType::MOVE, "Key E" });
			}
            else if (key == GLFW_KEY_ESCAPE)
            {
				g_global_context.m_input_manager->push(InputCommand{ CommandType::MOVE, "Key ESCAPE" });
			}
        }
        else if (action == GLFW_RELEASE)
        {
            if (key == GLFW_KEY_W)
            {
                g_global_context.m_input_manager->push(InputCommand{ CommandType::END_MOVE, "Key W" });
            }
            else if (key == GLFW_KEY_S)
            {
                g_global_context.m_input_manager->push(InputCommand{ CommandType::END_MOVE, "Key S" });
            }
            else if (key == GLFW_KEY_A)
            {
                g_global_context.m_input_manager->push(InputCommand{ CommandType::END_MOVE, "Key A" });
            }
            else if (key == GLFW_KEY_D)
            {
                g_global_context.m_input_manager->push(InputCommand{ CommandType::END_MOVE, "Key D" });
            }
            else if (key == GLFW_KEY_Q)
            {
                g_global_context.m_input_manager->push(InputCommand{ CommandType::END_MOVE, "Key Q" });
            }
            else if (key == GLFW_KEY_E)
            {
                g_global_context.m_input_manager->push(InputCommand{ CommandType::END_MOVE, "Key E" });
            }
            else if (key == GLFW_KEY_ESCAPE)
            {
                g_global_context.m_input_manager->push(InputCommand{ CommandType::END_MOVE, "Key ESCAPE" });
            }
        }
    }
    void GlfwWindow::onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT)
        {
            if (action == GLFW_PRESS) 
            {
                g_global_context.m_input_manager->push(InputCommand{ CommandType::CLICK, "Left Mouse Down" });
                m_dragging = true;
                glfwGetCursorPos(window, &m_last_x, &m_last_y);
            }
            else if (action == GLFW_RELEASE) 
            {
                g_global_context.m_input_manager->push(InputCommand{ CommandType::CLICK, "Left Mouse Up" });
                m_dragging = false;
            }
        }
        else if (button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            if (action == GLFW_PRESS)
            {
                g_global_context.m_input_manager->push(InputCommand{ CommandType::CLICK, "Right Mouse Down" });
            }
            else if (action == GLFW_RELEASE)
            {
                g_global_context.m_input_manager->push(InputCommand{ CommandType::CLICK, "Right Mouse Up" });
            }
        }
    }
    void GlfwWindow::onCursorPosCallback(GLFWwindow* window, double x_pos, double y_pos)
    {
        if (m_dragging)
        {
            double x_offset = x_pos - m_last_x;
            double y_offset = y_pos - m_last_y;
            m_last_x = x_pos;
            m_last_y = y_pos;
            if (abs(x_offset) > m_drag_threshold || abs(y_offset) > m_drag_threshold)
            {
                g_global_context.m_input_manager->push(InputCommand{ CommandType::DRAG, std::format("Drag x:{} y:{}", x_offset, y_offset) });
            }
            
        }
    }
}



