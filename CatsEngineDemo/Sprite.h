#pragma once
#include <GL/glew.h>
#include "Common.h"
#include "Texture.h"
#include <glm/vec2.hpp>
#include "Maths.h"

#define BindSprite(x) content.GetTexture(content.GetSprite(x).GetTexture()).Bind()

typedef uint SpriteHandle;

// texture atlas and coords
class Sprite
{
private:
	TextureHandle textureAtlas;
	vec4 rect;
	vec4 color;
public:
	Sprite();
	Sprite(TextureHandle texture, vec4 _rect);
	~Sprite();

	//void Init(TextureHandle texture, vec4 _rect);

	void SetRect(vec4 _rect) { rect = _rect; }
	void SetColor(vec4 _color) { color = _color; }

	TextureHandle & GetTexture() { return textureAtlas; }
	vec4 GetRect() { return rect; }
	vec4 GetColor() { return color; }
};

