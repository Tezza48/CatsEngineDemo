#pragma once
#include <glm/glm.hpp>

using namespace glm;

class Camera
{
private:
	vec3 position;

	// Settings
	float orthographicSize = 5.0f;
	float aspectRatio;

	// cache projection
	mat4 projection;
public:
	Camera();
	~Camera();

	void OnScreenResize(int newWidth, int newHeight);

	void Move2D(vec2 delta);

	mat4 GetViewProjection();

	inline void SetOrthographicSize(float newSize) { orthographicSize = newSize; }
};

