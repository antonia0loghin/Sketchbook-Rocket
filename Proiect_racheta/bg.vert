#version 330 core

layout (location = 0) in vec4 in_Position;
layout (location = 1) in vec2 in_TexCoord;

out vec2 TexCoord;

uniform float bgOffset;

void main(void)
{
    gl_Position = in_Position; 
    TexCoord = vec2(in_TexCoord.x, in_TexCoord.y + bgOffset);
}