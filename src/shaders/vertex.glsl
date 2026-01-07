#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 vertexColor;

out vec3 fragmentColor;

void main()
{
    // Must always set gl_Position in the vertex shader
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);

    fragmentColor = vertexColor;
}
