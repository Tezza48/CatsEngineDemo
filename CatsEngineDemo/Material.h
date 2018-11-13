#pragma once
#include <string>
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include "Common.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ContentManager.h"
#include "Texture.h"

using namespace glm;

typedef uint MaterialHandle;

// Has a list of passes (programs
// Content loader loads shader file and creates the programs
// Currently does single pass
class Material
{
protected:
	RendererID Shader;
	string name;

	//TextureHandle diffuseTextureHandle;
public:
	Material(string _shaderName = "default");
	virtual ~Material();

	// Loads and compiles the correct shaders
	bool Init();

	void Bind(ContentManager & content) const;

	inline void Unbind()
	{
		glUseProgram(0);
	}


	void SetWVP(mat4 wvp);
	//void SetSubRect();
	//void SetDiffuseTexture(TextureHandle handle) { diffuseTextureHandle = handle; }

	inline uint GetShaderProgram(){ return Shader; } // REMOVE THIS
	
public:
	// property setters, cache locations at some point
	template<typename T>
	bool SetProperty(const char * name, T value)
	{
		return false;
	}

	template<> bool SetProperty<glm::vec4>(const char * name, glm::vec4 value)
	{
		int location = glGetUniformLocation(Shader, name);
		if (location < 0) return false;

		glUniform4fv(location, 1, value_ptr(value));
		return true;
	}

	template<> bool SetProperty<glm::mat4>(const char * name, glm::mat4 value)
	{
		int location = glGetUniformLocation(Shader, name);
		if (location < 0) return false;

		glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(value));
		return true;
	}
};



