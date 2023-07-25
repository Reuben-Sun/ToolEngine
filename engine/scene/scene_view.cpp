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
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        std::vector<const char*> requiredExtensions;
        for (uint32_t i = 0; i < glfwExtensionCount; i++) {
            requiredExtensions.emplace_back(glfwExtensions[i]);
        }
        requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

        render = new Render();
        render->createInstance(requiredExtensions);
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

}