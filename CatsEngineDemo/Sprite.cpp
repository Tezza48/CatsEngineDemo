#include "Sprite.h"



Sprite::Sprite()
{
	textureAtlas = 0;
}

Sprite::Sprite(TextureHandle texture, vec4 _rect)
{
	textureAtlas = texture;
	rect = _rect;
}


Sprite::~Sprite()
{
}

void Sprite::SetTexture(TextureHandle _tex)
{
	textureAtlas = _tex;
}

//void Sprite::Init(TextureHandle texture, vec4 _rect)
//{
//
//}
