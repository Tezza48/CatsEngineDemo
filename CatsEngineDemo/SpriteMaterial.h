#pragma once
#include "Material.h"
class SpriteMaterial :
	public Material
{
private:
	TextureHandle texture;

	bool locationsFound = false;

	int wvpLocation;
	int subrectLocation;
	int colorLocation;

public:
	SpriteMaterial() : Material("sprite") {}
	~SpriteMaterial();

	void UploadResources(ContentManager & content);
};

