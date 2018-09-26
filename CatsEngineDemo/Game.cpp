#include "Game.h"

Game::~Game()
{
	glDeleteVertexArrays(1, &quad.vao);
}

void Game::Setup()
{
	App::Setup();

	mat.SetDiffuseTexture(content.LoadTexture("environment-desert.png"));

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
	wvp = cam.GetViewProjection();

	int wvpLocation = glGetUniformLocation(mat.GetShaderProgram(), "worldViewProj");
	glUniformMatrix4fv(wvpLocation, 1, GL_FALSE, &wvp[0][0]);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
