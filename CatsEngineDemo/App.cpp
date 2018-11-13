#include "App.h"
#include <stdio.h>

void GLAPIENTRY GLErrorCallback(GLenum _source, GLenum _type, GLuint _id, GLenum _severity, GLsizei length, const GLchar * _message, const void * userParam)
{
	const char * source;
	const char * type;
	const char * severity;

	// parse the error source
	switch (_source)
	{
	case GL_DEBUG_SOURCE_API:
		source = "GL";
		break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		source = "Window";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		source = "Shader Compiler";
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		source = "Third-Party";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		source = "User";
		break;
	case GL_DEBUG_SOURCE_OTHER:
		source = "Other";
		break;
	default:
		source = "Unknown";
		break;
	}
	switch (_type)
	{
	case GL_DEBUG_TYPE_ERROR:
		type = "ERROR";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		type = "Deprecated Behaviour";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		type = "Undefined Behaviour";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		type = "Portability";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		type = "Performance";
		break;
	case GL_DEBUG_TYPE_MARKER:
		type = "Marker";
		break;
	case GL_DEBUG_TYPE_PUSH_GROUP:
		type = "Push Group";
		break;
	case GL_DEBUG_TYPE_POP_GROUP:
		type = "Pop Group";
		break;
	case GL_DEBUG_TYPE_OTHER:
		type = "Other";
		break;
	default:
		type = "Unknown";
		break;
	}
	switch (_severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		severity = "HIGH";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		severity = "Medium";
		break;
	case GL_DEBUG_SEVERITY_LOW:
		severity = "Low";
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		severity = "Notification";
		break;
	default:
		severity = "Unknown, ";
		break;
	}

	printf("[%s %s] ID (%u), %s: %s\n", source, type, _id, severity, _message);
}

App::App()
{
	window = nullptr;
}


App::~App()
{
	glfwDestroyWindow(window);
}

bool App::Init()
{
	if (!glfwInit()) return false;

	// Version 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	glfwSwapInterval(1);

	#if DEBUG || _DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	#endif

	window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, ::Key_Callback);

	glewInit();

	#if DEBUG || _DEBUG
		//GLenum messageSources = 0;
		//messageSources |= GL_DEBUG_SOURCE_API;
		//messageSources |= GL_DEBUG_SOURCE_WINDOW_SYSTEM;
		//messageSources |= GL_DEBUG_SOURCE_SHADER_COMPILER;
		//messageSources |= GL_DEBUG_SOURCE_APPLICATION;

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
		glDebugMessageCallback(&GLErrorCallback, NULL);
	#endif

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glDisable(GL_DEPTH_TEST);

	return true;
}

void App::Run()
{
	Setup();

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		
		Update();
		Draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void App::Setup()
{
	time.Setup();
}

void App::Update()
{
	time.Update();
}

void App::Draw()
{
	
}

void Key_Callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(window, 1);
	}
}
