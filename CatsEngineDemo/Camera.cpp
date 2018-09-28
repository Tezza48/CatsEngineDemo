#include "Camera.h"

#include <glm/ext.hpp>

Camera::Camera()
{
}


Camera::~Camera()
{
}

//mat4 Camera::GetViewProjection()
//{
//	return projection * view; // backwards because it's transposed
//}

void Camera::CalculateView()
{
	view = lookAtLH(vec3(position, -10.0f), vec3(position, 0.0f), vec3(0.0f, 1.0f, 0.0f));
}

void Camera::CalculateProjection()
{
	vec2 offset = vec2(aspectRatio / 2.0f * orthographicSize, orthographicSize / 2.0f);
	projection = glm::ortho(-offset.x, offset.x, -offset.y, offset.y, plains.x, plains.y);
}

void Camera::OnScreenResize(int width, int height)
{
	aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	CalculateProjection();
}

void Camera::Move2D(vec2 delta)
{
	position += delta;
	CalculateView();
}

void Camera::SetPlanes(vec2 _plains)
{
	plains = _plains;
	CalculateProjection();
}

void Camera::SetOrthographicSize(float newSize)
{
	orthographicSize = newSize;
	CalculateProjection();
}

void Camera::SetPosition(vec2 _position)
{
	position = _position;
	CalculateView();
}
