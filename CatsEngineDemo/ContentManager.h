#pragma once
#include <stb/stb_image.h>
#include "Texture.h"
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
public:
	ContentManager();
	~ContentManager();

	uint LoadTexture(const char * filename);

	const Texture & GetTexture(uint id) const;
};

