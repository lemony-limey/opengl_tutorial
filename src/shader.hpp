//
// Created by Tom on 08/01/2026.
//

#ifndef OPENGL_TUTORIAL_SHADER_HPP
#define OPENGL_TUTORIAL_SHADER_HPP

// GLAD must be included so that all necessary OpenGL headers
// can be found.
#include <glad/glad.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


class shader
{
public:
    // Constructor reads and builds the shader
    shader(
        const std::string& vertex_shader_path,
        const std::string& fragment_shader_path
    );
    ~shader();

    // Use/activate the shader
    void use() const;

    // Utility uniform functions, which query a uniform location
    // and set its value.
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;

private:
    // Program ID
    unsigned int m_shader_program;

    // Helper functions for compiling the shader program.
    static unsigned int make_shader_module(const std::string& filepath, unsigned int module_type);
    static unsigned int make_shader_program(const std::string& vertex_filepath, const std::string& fragment_filepath);
};


#endif //OPENGL_TUTORIAL_SHADER_HPP