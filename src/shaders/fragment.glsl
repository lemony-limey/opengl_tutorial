#version 410 core
out vec4 FragColor;

in vec4 vVertexColor;
in vec2 vTexCoord;

uniform sampler2D uTexture;

void main()
{
    FragColor = texture(uTexture, vTexCoord);
}
