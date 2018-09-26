#pragma once
#include <glm/glm.hpp>

using namespace glm;

class Camera
{
private:
	vec2 position;

	// Settings
	float orthographicSize = 5.0f;
	float aspectRatio;

	// cache projection
	mat4 view;
	mat4 projection;
public:
	Camera();
	~Camera();

	void OnScreenResize(int newWidth, int newHeight);

	void Move2D(vec2 delta);

	//mat4 GetViewProjection();

	inline const mat4 & GetView() const { return view; }
	inline const mat4 & GetProjection() const { return projection; }

	void SetOrthographicSize(float newSize);
	void SetPosition(vec2 _position);

private:
	void CalculateView();
	void CalculateProjection();
};

