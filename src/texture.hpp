//
// Created by Tom on 08/01/2026.
//

#ifndef OPENGL_TUTORIAL_TEXTURE_HPP
#define OPENGL_TUTORIAL_TEXTURE_HPP

// This is the library for loading images.
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class texture
{
private:
    unsigned int m_height;
    unsigned int m_number_of_channels;
    unsigned int m_width;
    unsigned int m_texture;
};


#endif //OPENGL_TUTORIAL_TEXTURE_HPP