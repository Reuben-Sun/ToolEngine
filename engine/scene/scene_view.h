#pragma once

#include <iostream>
#include "GLFW/glfw3.h"
#include "render.h"

namespace ToolEngine
{
    class SceneView
    {
    public:
        SceneView();
        ~SceneView();
        void viewInit();
        void vulkanInit();
        void run();
        void cleanup();
        static void onErrorCallback(int error_code, const char* description)
        {
            std::cout << "Error" << std::endl;
        }
        
    private:
        GLFWwindow* window;
        Render* render;

        const int SAMPLE_WIDTH = 800;
        const int SAMPLE_HEIGHT = 400;
    };
}