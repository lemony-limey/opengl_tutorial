//
// Created by Tom on 07/01/2026.
//

#ifndef OPENGL_TUTORIAL_TRIANGLE_MESH_HPP
#define OPENGL_TUTORIAL_TRIANGLE_MESH_HPP


class triangle_mesh
{
public:
    triangle_mesh();
    void draw() const;
    ~triangle_mesh();

private:
    // Pointers to buffers
    unsigned int m_VAO{};
    unsigned int m_VBO{};
    unsigned int m_index_buffer{};

    // Additional info
    unsigned int m_vertex_count{};
    unsigned int m_index_count{};
};


#endif //OPENGL_TUTORIAL_TRIANGLE_MESH_HPP