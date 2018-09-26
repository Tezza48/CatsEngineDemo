#include "Material.h"

//#include <glm/gtc/type_ptr.hpp>

Material::Material()
{

}


Material::~Material()
{
}

void Material::Bind(ContentManager & content) const
{
	glUseProgram(shaderProgram);
	content.GetTexture(diffuseTextureHandle).Bind();
}

void Material::SetWVP(mat4 wvp)
{
	int wvpLocation = glGetUniformLocation(shaderProgram, "worldViewProj");
	glUniformMatrix4fv(wvpLocation, 1, GL_FALSE, &wvp[0][0]);
}

