#version 460 core

uniform mat4 worldViewProj;

layout(location = 0) in vec3 vertPosition;
layout(location = 1) in vec2 vertTex;
layout(location = 2) in vec4 vertColor;

out vec4 color;
out vec2 tex;

void main()
{
	gl_Position = vec4(vertPosition, 1.0) * worldViewProj;
	color = vertColor;
	tex = vertTex;
}