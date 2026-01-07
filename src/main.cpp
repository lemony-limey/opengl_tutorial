#include <iostream>

#include "config.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
unsigned int make_shader_module(const std::string& filepath, unsigned int module_type);
unsigned int make_shader_program(const std::string& vertex_filepath, const std::string& fragment_filepath);
void processInput(GLFWwindow* window);

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

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

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glClearColor is a state-setting function
    glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

    unsigned int shader;
    try
    {
        shader = make_shader_program(
            "../src/shaders/vertex.txt",
            "../src/shaders/fragment.txt"
        );
    }
    catch (...)
    {
        std::cout << "An exception occurred when creating the shader program" << std::endl;
        return 1;
    }

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // glClear is a state-using function
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}


// Called whenever the window size changes (by the user or the OS).
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


// Takes a shader source file and compiles it into a shader module.
unsigned int make_shader_module(const std::string& filepath, unsigned int module_type)
{
    std::ifstream file;
    std::stringstream bufferedLines;
    std::string line;

    // Open the file and collect its contents line-by-line into bufferedLines.
    file.open(filepath);
    while (std::getline(file, line))
    {
        bufferedLines << line << '\n';
    }
    std::string shaderSource = bufferedLines.str();
    const char* shaderSrc = shaderSource.c_str();
    bufferedLines.str("");
    file.close();

    // Compile the shader module.
    unsigned int shaderModule = glCreateShader(module_type);
    glShaderSource(shaderModule, 1, &shaderSrc, nullptr);
    glCompileShader(shaderModule);

    // Check for success
    int success;
    glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char errorLog[1024];
        glGetShaderInfoLog(shaderModule, 1024, nullptr, errorLog);
        std::cout << "Shader Module compilation error: \n" << errorLog << std::endl;
        throw std::runtime_error("Oof");
    }

    return shaderModule;
}


//
unsigned int make_shader_program(const std::string& vertex_filepath, const std::string& fragment_filepath)
{
    std::vector<unsigned int> modules;
    modules.push_back(make_shader_module(vertex_filepath, GL_VERTEX_SHADER));
    modules.push_back(make_shader_module(fragment_filepath, GL_FRAGMENT_SHADER));

    // Create necessary modules and link them
    unsigned int shader = glCreateProgram();
    for (unsigned int shaderModule : modules)
    {
        glAttachShader(shader, shaderModule);
    }
    glLinkProgram(shader);

    // Check for success
    int success;
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success)
    {
        char errorLog[1024];
        glGetShaderInfoLog(shader, 1024, nullptr, errorLog);
        std::cout << "Shader Program linking error: \n" << errorLog << std::endl;
        throw std::runtime_error("Oof");
    }

    // Modules can be deleted once the shader program is linked.
    for (unsigned int shaderModule : modules)
    {
        glDeleteShader(shaderModule);
    }

    return shader;
}


// Check if relevant keys are pressed/released.
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}


