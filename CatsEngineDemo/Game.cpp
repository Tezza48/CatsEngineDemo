#include "Game.h"

#include "Texture.h"

Game::~Game()
{
	glDeleteVertexArrays(1, &quad.vao);
}

void Game::Setup()
{
	App::Setup();

	TextureHandle envTexture = content.LoadTexture("environment-desert.png");

	cactusSprite.Init(envTexture, vec4(0.012f, 0.015f, 0.3f, 0.45f));

	mat.SetDiffuseTexture(envTexture);

	cam.SetPosition(vec2(0.0f, 0.0f));
	cam.SetOrthographicSize(1.0f);
	cam.OnScreenResize(GetWindowWidth(), GetWindowHeight());

	quad.Init();

	mat.Load();

	clearColor = vec4(0.98f, 0.8f, 0.5f, 1.0f);
}

void Game::Update()
{
	App::Update();

}

void Game::Draw()
{
	mat.Bind(content);
	quad.Bind();
	//glBindVertexArray(quad.vao);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad.iBuffer);

	mat4 wvp;
	wvp = cam.GetProjection()/* * cam.GetView()*/;

	int wvpLocation = glGetUniformLocation(mat.GetShaderProgram(), "worldViewProj");
	glUniformMatrix4fv(wvpLocation, 1, GL_FALSE, &wvp[0][0]);

	int subrectLocation = glGetUniformLocation(mat.GetShaderProgram(), "subrect");
	glUniform4fv(subrectLocation, 1, glm::value_ptr(cactusSprite.GetRect()));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
