#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "GameTimer.h"
#include <glm/vec4.hpp>

using std::string;
using glm::vec4;

//void GLAPIENTRY GLErrorCallback(GLenum source,
//	GLenum type,
//	GLuint id,
//	GLenum severity,
//	GLsizei length,
//	const GLchar *message,
//	void *userParam);

/*
 * TODO:
 * Batch Renderer
 */



 void Key_Callback(GLFWwindow * window, int key, int scancode, int action, int mods);

class App
{
public:
private:
	int windowWidth = 800;
	int windowHeight = 600;
	string windowTitle = "2D GL Engine";

	GLFWwindow * window;

protected:
	GameTimer time;
	vec4 clearColor;
	
public:
	App();
	virtual ~App();

	bool Init();
	void Run();

protected:
	virtual void Setup();
	virtual void Update();
	virtual void Draw();

	inline void SetWindowTitle(const char * newTitle) { windowTitle = newTitle; }
	inline void SetWindowSize(int width, int height) { windowWidth = width; windowHeight = height; }

	inline int GetWindowWidth() { return windowWidth; }
	inline int GetWindowHeight() { return windowHeight; }

};

