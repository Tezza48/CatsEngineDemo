#include "Camera.h"

#include <glm/ext.hpp>

Camera::Camera()
{
}


Camera::~Camera()
{
}

mat4 Camera::GetViewProjection()
{
	mat4 view = lookAt(position, position + vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	return projection/* * view*/; // backwards because it's transposed
}

void Camera::OnScreenResize(int width, int height)
{
	aspectRatio = static_cast<float>(width) / static_cast<float>(height);

	vec2 offset = vec2(aspectRatio / 2.0f * orthographicSize, orthographicSize / 2.0f);
	projection = ortho(-offset.x, offset.x, -offset.y, offset.y);
}

void Camera::Move2D(vec2 delta)
{
	position += vec3(delta.x, delta.y, 0.0f);
}
