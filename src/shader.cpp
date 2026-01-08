//
// Created by Tom on 08/01/2026.
//

#include "shader.hpp"

shader::shader(
    const std::string& vertex_shader_path,
    const std::string& fragment_shader_path
)
{
    // THROWS: runtime exception on failure
    m_shader_program = make_shader_program(
        vertex_shader_path,
        fragment_shader_path
    );
}

shader::~shader()
{
    glDeleteProgram(m_shader_program);
}


void shader::use() const
{
    glUseProgram(m_shader_program);
}

void shader::setBool(const std::string& name, const bool value) const
{
    glUniform1i(
        glGetUniformLocation(m_shader_program, name.c_str()),
        static_cast<int>(value)
    );
}

void shader::setInt(const std::string& name, const int value) const
{
    glUniform1i(
        glGetUniformLocation(m_shader_program, name.c_str()),
        value
    );
}

void shader::setFloat(const std::string& name, const float value) const
{
    glUniform1f(
        glGetUniformLocation(m_shader_program, name.c_str()),
        value
    );
}


// Takes a shader source file and compiles it into a shader module.
// THROWS: runtime exception on failure.
//
// This functions is from:
// https://www.youtube.com/watch?v=HdNaUwYc8_A
unsigned int shader::make_shader_module(const std::string& filepath, unsigned int module_type)
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
    // On failure, throw an exception.
    if (!success)
    {
        char errorLog[1024];
        glGetShaderInfoLog(shaderModule, 1024, nullptr, errorLog);
        std::cerr << "ERROR: Shader Module compilation error: \n" << errorLog << std::endl;
        throw std::runtime_error("Oof");
    }

    return shaderModule;
}


// Links two shader modules together to create a shader program.
// THROWS: runtime exception on failure.
//
// This function is from:
// https://www.youtube.com/watch?v=HdNaUwYc8_A
unsigned int shader::make_shader_program(const std::string& vertex_filepath, const std::string& fragment_filepath)
{
    std::vector<unsigned int> modules;
    // Each of the two calls to make_shader_module can throw a runtime exception on failure.
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
    // On failure, throw an exception.
    if (!success)
    {
        char errorLog[1024];
        glGetShaderInfoLog(shader, 1024, nullptr, errorLog);
        std::cerr << "ERROR: Shader Program linking error: \n" << errorLog << std::endl;

        throw std::runtime_error("Oof");
    }

    // Modules can be deleted once the shader program is linked.
    for (unsigned int shaderModule : modules)
    {
        glDeleteShader(shaderModule);
    }

    std::cout << "INFO: Shader program created successfully." << std::endl;
    return shader;
}
