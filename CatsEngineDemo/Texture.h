#pragma once
#include <GL/glew.h>
#include "Common.h"
#include <glm/glm.hpp>
#include <vector>

using std::vector;
using namespace glm;

class Texture
{
private:
	uint textureHandle;
	int width, height, numChannels;
public:
	Texture(byte * data, int _width, int _height, int _numChannels);
	~Texture();

	void Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, textureHandle);
	}
};

