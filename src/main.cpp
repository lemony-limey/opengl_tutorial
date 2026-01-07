#include <iostream>

#include "GLFW/glfw3.h"


int main()
{
    GLFWwindow* window;

    if (!glfwInit())
    {
        std::cout << "GLFW couldn't be initialised." << std::endl;
        return 1;
    }

    window = glfwCreateWindow(640, 400, "My Window", nullptr, nullptr);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
