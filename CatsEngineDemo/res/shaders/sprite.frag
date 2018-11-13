#version 460 core

uniform sampler2D diffuseTexture;

in vec4 color;
in vec2 tex;

out vec4 FragColor;

void main()
{
	vec4 diffuseColor = texture2D(diffuseTexture, tex);
	if(diffuseColor.a < 0.5) discard;
	FragColor = diffuseColor * color;
}