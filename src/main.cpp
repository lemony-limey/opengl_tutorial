#include <iostream>
#include <memory>

#include "config.hpp"
#include "shader.hpp"
#include "triangle_mesh.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// constexpr is instantiated at compile time.
constexpr unsigned int SCREEN_WIDTH  = 800;
constexpr unsigned int SCREEN_HEIGHT = 600;

// const could be instantiated at runtime or compile time.
const std::string VERTEX_SHADER_PATH = "../src/shaders/vertex.glsl";
const std::string FRAGMENT_SHADER_PATH = "../src/shaders/fragment.glsl";

int main()
{
    GLFWwindow* window;

    if (!glfwInit())
    {
        std::cout << "GLFW couldn't be initialised." << std::endl;
        return 1;
    }

    // Make the window and set it as the current opengl context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My Window", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // Find all of the OpenGL procedures.
    // These are defined in GLAD and not OpenGL, because OpenGL itself is just
    // a specification.

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        glfwTerminate();
        return 1;
    }

    // Print the number of vertex attributes OpenGL allows
    int number_of_attributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &number_of_attributes);
    std::cout << "Maximum number of vertex attributes supported: " << number_of_attributes << std::endl;

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glClearColor is a state-setting function
    glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

    std::unique_ptr<triangle_mesh> triangle = std::make_unique<triangle_mesh>();

    try
    {
        shader current_shader(
            VERTEX_SHADER_PATH,
            FRAGMENT_SHADER_PATH
        );

        // Render loop
        while (!glfwWindowShouldClose(window))
        {
            processInput(window);

            // glClear is a state-using function
            glClear(GL_COLOR_BUFFER_BIT);
            current_shader.use();
            triangle->draw();

            glfwPollEvents();
            glfwSwapBuffers(window);
        }

        glfwTerminate();
        return 0;
    }
    catch (...)
    {
        std::cerr << "Oof" << std::endl;
        return 1;
    }
}


// Called whenever the window size changes (by the user or the OS).
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


// Check if relevant keys are pressed/released.
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
