//
// Created by Tom on 07/01/2026.
//

#ifndef OPENGL_TUTORIAL_TRIANGLE_MESH_HPP
#define OPENGL_TUTORIAL_TRIANGLE_MESH_HPP

#include <memory>

#include "texture.hpp"


class triangle_mesh
{
public:
    triangle_mesh(const std::shared_ptr<texture>& current_texture);
    void draw() const;
    ~triangle_mesh();

private:
    // Pointers to buffers
    unsigned int m_VAO{};
    unsigned int m_VBO{};
    unsigned int m_index_buffer{};
    std::shared_ptr<texture> m_current_texture = nullptr;

    // Additional info
    unsigned int m_vertex_count{};
    unsigned int m_index_count{};
};


#endif //OPENGL_TUTORIAL_TRIANGLE_MESH_HPP