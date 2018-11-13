#pragma once
#include <stb/stb_image.h>
#include "Texture.h"
#include "Sprite.h"
#include <vector>
#include <string>
#include "Common.h"

#define RESOURCE_PATH "res/"
#define TEX_PATH "textures/"

using std::vector;
using std::string;

class ContentManager
{
private:
	vector<Texture> textures;
	vector<Sprite> sprites;
public:
	ContentManager();
	~ContentManager();

	TextureHandle LoadTexture(const char * filename);
	SpriteHandle RegisterSprite(Sprite sprite);

	Texture & GetTexture(TextureHandle id);
	Sprite & GetSprite(SpriteHandle id);
};

