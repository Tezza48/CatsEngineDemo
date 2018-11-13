#include "SpriteMaterial.h"


SpriteMaterial::~SpriteMaterial()
{
}

void SpriteMaterial::UploadResources(ContentManager & content)
{
	if (!locationsFound)
	{
		wvpLocation = glGetUniformLocation(Shader, "worldViewProj");
		subrectLocation = glGetUniformLocation(Shader, "subrect");
		colorLocation = glGetUniformLocation(Shader, "colorOverride");
	}
}
