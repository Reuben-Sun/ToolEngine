#include "scene_view.h"

namespace ToolEngine
{
    SceneView::SceneView()
    {
    }

    SceneView::~SceneView()
    {
    }

    void SceneView::viewInit()
    {
        glfwSetErrorCallback(onErrorCallback);
        if (!glfwInit()) { return; }
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        char* PROJECT_NAME = "Test";
        window = glfwCreateWindow(SAMPLE_WIDTH, SAMPLE_HEIGHT, PROJECT_NAME, nullptr, nullptr);
    }

    void SceneView::vulkanInit()
    {
        render = new Render();
        render->createInstance(getRequiredExtensions());
        render->setupDebugMessenger();
        render->setupDevice();
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
        render->destroyInstance();
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    std::vector<const char*> SceneView::getRequiredExtensions()
    {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
        return extensions;
    }

}