#include "Material.h"


Material::Material(string _name)
{
	name = _name;
}

Material::~Material()
{
}

bool Material::Init()
{
	Shader = glCreateProgram();
	uint vs = glCreateShader(GL_VERTEX_SHADER);
	uint fs = glCreateShader(GL_FRAGMENT_SHADER);

	std::ifstream file("res/shaders/" + name + ".vert");
	if (!file.is_open()) return false;

	std::stringstream vsStream;
	vsStream << file.rdbuf();
	std::string vsSource = vsStream.str();
	file.close();

	file.open("res/shaders/" + name + ".frag", std::ifstream::in);
	if (!file.is_open()) return false;

	std::stringstream fsStream;
	fsStream << file.rdbuf();
	std::string fsSource = fsStream.str();
	file.close();

	int success;

	const char * vscstr = vsSource.c_str();
	glShaderSource(vs, 1, &vscstr, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (success != GL_TRUE)
	{
		int length = 0;
		char message[1024];
		glGetShaderInfoLog(vs, 1024, &length, message);
		printf("Vertex Shader COMPILATION ERROR: %s\n", message);
		return false;
	}

	const char * fscstr = fsSource.c_str();
	glShaderSource(fs, 1, &fscstr, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (success != GL_TRUE)
	{
		int length = 0;
		char message[1024];
		glGetShaderInfoLog(fs, 1024, &length, message);
		printf("Frag Shader COMPILATION ERROR: %s\n", message);
		return false;
	}

	glAttachShader(Shader, vs);
	glAttachShader(Shader, fs);
	glLinkProgram(Shader);

	return true;
}

void Material::Bind(ContentManager & content) const
{
	glUseProgram(Shader);
	//content.GetTexture(diffuseTextureHandle).Bind();
}

void Material::SetWVP(mat4 wvp)
{
	int wvpLocation = glGetUniformLocation(Shader, "worldViewProj");
	glUniformMatrix4fv(wvpLocation, 1, GL_FALSE, &wvp[0][0]);
}

