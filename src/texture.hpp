//
// Created by Tom on 08/01/2026.
//

#ifndef OPENGL_TUTORIAL_TEXTURE_HPP
#define OPENGL_TUTORIAL_TEXTURE_HPP


#include <glad/glad.h>

#include <string>


class texture
{
public:
    texture(const std::string& image_file);

    unsigned int get_texture_location() const;
private:
    unsigned int m_texture = 0;

    int m_height = 0;
    int m_number_of_channels = 0;
    int m_width = 0;
};


#endif //OPENGL_TUTORIAL_TEXTURE_HPP