#include "ContentManager.h"



ContentManager::ContentManager()
{
}


ContentManager::~ContentManager()
{
}

uint ContentManager::LoadTexture(const char * filename)
{
	//TODO: Cache the loaded texture

	string path = RESOURCE_PATH;
	path += TEX_PATH;
	path += filename;

	int width, height, numChannels;

	stbi_set_flip_vertically_on_load(true);

	byte * data = stbi_load(path.c_str(), &width, &height, &numChannels, 0);

	textures.push_back(Texture(data, width, height, numChannels));

	stbi_image_free(data);

	return textures.size() - 1;
}

SpriteHandle ContentManager::RegisterSprite(Sprite sprite)
{
	sprites.push_back(sprite);
	return sprites.size() - 1;
}

Sprite & ContentManager::GetSprite(SpriteHandle id)
{
	return sprites[id];
}

Texture & ContentManager::GetTexture(uint id)
{
	// TODO: insert return statement here
	return textures[id];
}
