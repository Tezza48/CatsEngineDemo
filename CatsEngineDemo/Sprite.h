#pragma once
#include <GL/glew.h>
#include "Common.h"
#include "Texture.h"
#include <glm/vec2.hpp>
#include "Maths.h"

// texture atlas and coords
class Sprite
{
private:
	TextureHandle textureAtlas;
	vec4 rect;

public:
	Sprite();
	~Sprite();

	void Init(TextureHandle texture, vec4 _rect);

	TextureHandle GetTexture() { return textureAtlas; }
	vec4 GetRect() { return rect; }
};

