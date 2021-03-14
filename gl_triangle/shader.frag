#version 330 core

in vec3 fsColor;
in vec2 fsTexCoord;

out vec4 color;

uniform sampler2D fsTexture;
uniform sampler2D fsTexture2;
uniform float factor;

void main()
{
	color = mix(texture(fsTexture, fsTexCoord), texture(fsTexture2, vec2(1.0 - fsTexCoord.x, 1.0 - fsTexCoord.y)), factor);
}