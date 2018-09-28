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

	//cactusSprite.Init(envTexture, vec4(0.0f, 0.0f, 1.0f, 1.0f));
	cactusSprite.Init(envTexture, vec4(0.012f, 0.015f, 0.3f, 0.45f));

	mat.SetDiffuseTexture(envTexture);

	cam.SetPosition(vec2(0.0f, 0.0f));
	cam.SetOrthographicSize(5.0f);
	cam.SetPlanes(vec2(0.1f, 100.0f));
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

	vec3 circularPos = vec3(sin(time.GetTime() / 2.0f) * 2.0f, 0.0f, glm::cos(time.GetTime() / 2.0f) * 2.0f);


	mat4 view = mat4(1.0f);
	view = lookAt(vec3(0.0f, 0.0f, -5.0f), vec3(0.0f), vec3(0.0f, 1.0f, 0.0f));
	
	mat4 proj;
	proj = cam.GetProjection();
	proj = [](float aspect, float size) -> mat4
	{
		vec2 offset = vec2(aspect / 2.0f * size, size / 2.0f);
		return glm::ortho(-offset.x, offset.x, -offset.y, offset.y, 0.1f, 100.0f);
	}(cam.GetAspectRatio(), 5.0f);
	//proj = glm::perspective(3.14159f / 4.0f, cam.GetAspectRatio(), 0.1f, 100.0f);


	mat4 wvp = mat4(1.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	int subrectLocation = glGetUniformLocation(mat.GetShaderProgram(), "subrect");
	glUniform4fv(subrectLocation, 1, glm::value_ptr(cactusSprite.GetRect()));

	int colorLocation = glGetUniformLocation(mat.GetShaderProgram(), "colorOverride");
	glUniform4f(colorLocation, 0.1f, 0.8f, 0.1f, 1.0f);

	int wvpLocation = glGetUniformLocation(mat.GetShaderProgram(), "worldViewProj");

	// Drawing the sprites
	//wvp = cam.GetProjection() * cam.GetView() * glm::translate(mat4(1.0f), circularPos);
	wvp = proj * view * glm::translate(mat4(1.0f), circularPos);
	glUniformMatrix4fv(wvpLocation, 1, GL_FALSE, &wvp[0][0]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	//wvp = cam.GetProjection() * cam.GetView() * mat4(1.0f);
	wvp = proj * view * mat4(1.0f);
	glUniformMatrix4fv(wvpLocation, 1, GL_FALSE, &wvp[0][0]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

}
