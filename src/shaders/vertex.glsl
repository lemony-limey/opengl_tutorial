#version 410 core
// Attributes
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;
layour (location = 2) in vec2 aTexCoord;

// Varying
out vec4 vVertexColor;
out vec2 vTexCoord;

void main()
{
    // Must always set gl_Position in the vertex shader
    gl_Position = vec4(aPos, 1.0);

    vVertexColor = vec4(aColor, 1.0);
    vTexCoord = aTexCoord;
}
