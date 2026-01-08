//
// Created by Tom on 07/01/2026.
//

#include "triangle_mesh.hpp"
#include "texture.hpp"

#include <vector>
#include <glad/glad.h>

triangle_mesh::triangle_mesh(const std::shared_ptr<texture>& current_texture)
{
    m_current_texture = current_texture;

    // Coordinates of each vertex and the colour at each vertex.
    std::vector<float> vertices = {
        // Positions ------   // Colours ------   // Texture coordinates
        -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // Bottom Left
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
         0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.5f, 0.5f, // Top Centre
    };
    m_vertex_count = vertices.size();
    // Vertices that constitute each triangle.
    std::vector<unsigned int> indices = {
        0, 1, 2,
    };
    m_index_count = indices.size();

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    // Copy the contents of the vertices array into the currently bound buffer for
    // OpenGL to use.
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        m_vertex_count * sizeof(float),
        vertices.data(),
        GL_STATIC_DRAW
    );

    // Define the positions of each component in the vertex buffer object.
    // Positions (x, y, z)
    constexpr GLsizei stride = 8 * sizeof(float);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, nullptr);
    glEnableVertexAttribArray(0);

    // Colours (r, g, b)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture coordinates (u, v)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // Perform the same for the indices
    glGenBuffers(1, &m_index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(unsigned int),
        indices.data(),
        GL_STATIC_DRAW
    );
}


void triangle_mesh::draw() const
{
    glBindTexture(GL_TEXTURE_2D, m_current_texture->get_texture_location());
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, nullptr);
    // No need to unbind the VAO every time, but here is the code to do so if necessary:
    // glBindVertexArray(0);
}


// Buffers are deallocated before the triangle_mesh itself to ensure no resources
// are leaked.
triangle_mesh::~triangle_mesh()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_index_buffer);
}
