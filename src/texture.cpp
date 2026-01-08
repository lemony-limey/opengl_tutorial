//
// Created by Tom on 08/01/2026.
//


// This is the library for loading images.
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "texture.hpp"

#include <iostream>


// THROWS: a runtime error if loading the texture image fails
texture::texture(const std::string& image_file)
{
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    // Flip the y-axis when loading the image so (0, 0) is at the bottom left.
    stbi_set_flip_vertically_on_load(true);

    // Load the image data and generate the texture.
    unsigned char* data = stbi_load(
        image_file.c_str(),
        &m_width,
        &m_height,
        &m_number_of_channels,
        0
    );
    if (data)
    {
        std::cout << "INFO: Successfully loaded texture image." << std::endl;
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGB,
            m_width,
            m_height,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            data
        );
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "ERROR: Failed to load texture." << std::endl;
        throw std::runtime_error("Failed to load texture.");
    }

    // Good practice to free the image memory.
    stbi_image_free(data);
}


unsigned int texture::get_texture_location() const
{
    return this->m_texture;
}
