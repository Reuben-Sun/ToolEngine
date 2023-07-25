#include "scene_view.h"

namespace ToolEngine
{
    SceneView::SceneView()
    {
    }

    SceneView::~SceneView()
    {
    }

    void SceneView::init()
    {
        glfwSetErrorCallback(onErrorCallback);
        if (!glfwInit()) { return; }
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        char* PROJECT_NAME = "Test";
        window = glfwCreateWindow(SAMPLE_WIDTH, SAMPLE_HEIGHT, PROJECT_NAME, nullptr, nullptr);
    }
    
    void SceneView::run()
    {
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
        }
    }

    void SceneView::cleanup()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

}