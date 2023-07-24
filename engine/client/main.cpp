#include <iostream>
#include "GLFW/glfw3.h"

static void onErrorCallback(int error_code, const char* description)
{
    std::cout << "Error" << std::endl;
}

int main(){
    const int SAMPLE_WIDTH = 800;
    const int SAMPLE_HEIGHT = 400;
    char* PROJECT_NAME = "Test";
    glfwSetErrorCallback(onErrorCallback);
    if (!glfwInit()) { return 1; }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(SAMPLE_WIDTH, SAMPLE_HEIGHT, PROJECT_NAME, nullptr, nullptr);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}