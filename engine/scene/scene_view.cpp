#include "scene_view.h"

namespace ToolEngine
{
    SceneView::SceneView()
    {
    }

    SceneView::~SceneView()
    {
    }
    
    void SceneView::run()
    {
        glfwSetErrorCallback(onErrorCallback);
        if (!glfwInit()) { return; }
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        char* PROJECT_NAME = "Test";
        GLFWwindow* window = glfwCreateWindow(SAMPLE_WIDTH, SAMPLE_HEIGHT, PROJECT_NAME, nullptr, nullptr);
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
        }
        glfwDestroyWindow(window);
        glfwTerminate();
    }

}