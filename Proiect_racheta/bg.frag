#version 330 core

in vec2 TexCoord;
out vec4 out_Color;

uniform sampler2D bgTexture;

void main(void)
{
    out_Color = texture(bgTexture, TexCoord);
}