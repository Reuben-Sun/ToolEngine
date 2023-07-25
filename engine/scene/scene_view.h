#pragma once

#include "GLFW/glfw3.h"
#include <iostream>

namespace ToolEngine
{
    class SceneView
    {
    public:
        SceneView();
        ~SceneView();
        static void run();
        static void onErrorCallback(int error_code, const char* description)
        {
            std::cout << "Error" << std::endl;
        }
        const static int SAMPLE_WIDTH = 800;
        const static int SAMPLE_HEIGHT = 400;
    private:

    };
}