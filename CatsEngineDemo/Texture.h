#pragma once
#include <GL/glew.h>
#include "Common.h"
#include <glm/glm.hpp>
#include <vector>

#define BindTexture(x) content.GetTexture(x).Bind();

using std::vector;
using namespace glm;

typedef uint TextureHandle;

class Texture
{
private:
	uint glTexture;
	int width, height, numChannels;
public:
	Texture(byte * data, int _width, int _height, int _numChannels);
	~Texture();

	void Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, glTexture);
	}
};

