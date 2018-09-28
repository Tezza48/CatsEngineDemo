#version 460 core

uniform sampler2D diffuseTexture;

in vec4 color;
in vec2 tex;

out vec4 FragColor;

void main()
{
	FragColor = texture2D(diffuseTexture, tex) * color;
}