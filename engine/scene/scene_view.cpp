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
        glfwGetFramebufferSize(window, &render->frameWidth, &render->frameHeight);
        render->createInstance(getRequiredExtensions());
        render->setupDebugMessenger();
        render->setupSurface(window);
        render->setupPhysicalDevice();
        render->setupLogicalDevice();
        render->setupSwapChain();
        render->setupImageViews();
        render->createRenderPass();
        render->setupGraphicsPipeline();
        render->setupFrameBuffers();
        render->setupCommandPool();
        render->setupCommandBuffer();
        render->setupSyncObjects();
    }
    
    void SceneView::mainLoop()
    {
        while (!glfwWindowShouldClose(window))
        {
            OPTICK_FRAME("MainThread")
            glfwPollEvents();
            render->drawFrame();
        }
    }

    void SceneView::cleanup()
    {
        render->destroySyncObjects();
        render->destroyCommandPool();
        render->destroyFrameBuffers();
        render->destroyPipeline();
        render->destroyRenderPass();
        render->destroyImageViews();
        render->destroySwapChain();
        render->destroySurface();
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