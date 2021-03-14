#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vsColor;
layout (location = 2) in vec2 vsTexCoord;

out vec3 fsColor;
out vec2 fsTexCoord;

void main()
{
    gl_Position = vec4(position, 1.0);
    fsColor = vsColor;
    fsTexCoord = vsTexCoord;
}