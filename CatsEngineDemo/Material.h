#pragma once
#include <string>
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include "Common.h"
#include <glm/glm.hpp>
#include "ContentManager.h"

using namespace glm;

// Has a list of passes (programs
// Content loader loads shader file and creates the programs
// Currently does single pass
class Material
{
private:
	uint shaderProgram;

	uint diffuseTextureHandle;
public:
	Material();
	~Material();

	//void Init();

	// Should be responsibility of asset loader
	inline bool Load()
	{
		shaderProgram = glCreateProgram();
		uint vs = glCreateShader(GL_VERTEX_SHADER);
		uint fs = glCreateShader(GL_FRAGMENT_SHADER);

		std::ifstream file("res/shaders/default.vert");
		if (!file.is_open()) return false;
		
		std::stringstream vsStream;
		vsStream << file.rdbuf();
		std::string vsSource = vsStream.str();
		file.close();

		file.open("res/shaders/default.frag", std::ifstream::in);
		if (!file.is_open()) return false;

		std::stringstream fsStream;
		fsStream << file.rdbuf();
		std::string fsSource = fsStream.str();
		file.close();

		int success;

		const char * vscstr = vsSource.c_str();
		glShaderSource(vs, 1, &vscstr, NULL);		
		glCompileShader(vs);
		glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
		if (success != GL_TRUE)
		{
			int length = 0;
			char message[1024];
			glGetShaderInfoLog(vs, 1024, &length, message);
			printf("Vertex Shader COMPILATION ERROR: %s\n", message);
			return false;
		}
		
		const char * fscstr = fsSource.c_str();
		glShaderSource(fs, 1, &fscstr, NULL);
		glCompileShader(fs);
		glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
		if (success != GL_TRUE)
		{
			int length = 0;
			char message[1024];
			glGetShaderInfoLog(fs, 1024, &length, message);
			printf("Frag Shader COMPILATION ERROR: %s\n", message);
			return false;
		}

		glAttachShader(shaderProgram, vs);
		glAttachShader(shaderProgram, fs);
		glLinkProgram(shaderProgram);

		return true;
	}

	void Bind(ContentManager & content) const;

	inline void Unbind()
	{
		glUseProgram(0);
	}

	void SetWVP(mat4 wvp);
	void SetDiffuseTexture(uint handle) { diffuseTextureHandle = handle; }

	inline uint GetShaderProgram(){ return shaderProgram; } // REMOVE THIS
};

