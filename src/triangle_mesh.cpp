//
// Created by Tom on 07/01/2026.
//

#include "triangle_mesh.hpp"
#include <vector>
#include <glad/glad.h>

triangle_mesh::triangle_mesh()
{
    std::vector<float> data = {
        -0.5f, -0.5f, 0.0f,
         1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  1.0f, 0.0f,
         0.0f,  0.5f, 0.0f,
         0.0f,  0.0f, 1.0f
    };
    m_vertex_count = 3;

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        data.size() * sizeof(float),
        data.data(),
        GL_STATIC_DRAW
    );

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, nullptr);
    glEnableVertexAttribArray(0);

    // Colour
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, reinterpret_cast<void*>(12));
    glEnableVertexAttribArray(1);
}


void triangle_mesh::draw() const
{
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, m_vertex_count);
}


triangle_mesh::~triangle_mesh()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
}
