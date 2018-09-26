#include "Sprite.h"



Sprite::Sprite()
{
	
}


Sprite::~Sprite()
{
}

void Sprite::Init(TextureHandle texture, vec4 _rect)
{
	textureAtlas = texture;
	rect = _rect;
}
