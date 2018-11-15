#version 460 core

uniform mat4 worldViewProj;
uniform vec4 subrect = vec4(0.0, 0.0, 1.0, 1.0);
uniform vec4 colorOverride = vec4(1.0);

layout(location = 0) in vec3 vertPosition;
layout(location = 1) in vec2 vertTex;
layout(location = 2) in vec4 vertColor;

out vec4 color;
out vec2 tex;

void main()
{
	float ratio = (subrect.z - subrect.x) / (subrect.w - subrect.y);

	mat2 rectScale = mat2(1.0);
	rectScale[0][0] = ratio;

	gl_Position = worldViewProj * mat4(rectScale) * vec4(vertPosition, 1.0);
	color = colorOverride;

	tex = vertTex * subrect.zw + subrect.xy;
}