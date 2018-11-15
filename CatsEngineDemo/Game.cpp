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
	Sprite cactusSprite = Sprite(envTexture, /*vec4(0.012f, 0.015f, 0.3f, 0.45f)*/vec4(0.0f, 0.0f, 1.0f, 1.0f));
	SpriteHandle cactusID = content.RegisterSprite(Sprite(envTexture, vec4(0.012f, 0.015f, 0.3f, 0.45f)));
	content.GetSprite(cactusID).SetColor(glm::vec4(0.15f, 0.8f, 0.15f, 1.0f));

	mat = Material("sprite");
	mat.Init();

	quad.Init();

	cam.SetPosition(vec2(0.0f, 0.0f));
	cam.SetOrthographicSize(10.0f);
	cam.SetPlanes(vec2(0.1f, 100.0f));
	cam.OnScreenResize(GetWindowWidth(), GetWindowHeight());

	clearColor = vec4(0.98f, 0.8f, 0.5f, 1.0f);

	objects.push_back(GameObject());
	objects[0].SetSprite(cactusID);
	objects[0].SetPosition(glm::vec3());
	//objects.push_back(GameObject());
	//objects[1].SetSprite(cactusID);
	//objects[1].SetPosition(glm::vec3());
}

void Game::Update()
{
	App::Update();

	objects[0].SetPosition(glm::vec3(sin(time.GetTime()), 0.0f, 0.0f));

}

void Game::Draw()
{
	mat.Bind(content);
	quad.Bind();

	mat4 wvp = mat4(1.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	BindSprite(objects[0].GetSprite());
	mat.SetProperty("subrect", content.GetSprite(objects[0].GetSprite()).GetRect());
	mat.SetProperty("colorOverride", content.GetSprite(objects[0].GetSprite()).GetColor());

	
	for (size_t y = 0; y < 10; y++)
	{
		for (size_t x = 0; x < 10; x++)
		{
			wvp = cam.GetProjection() * cam.GetView() * glm::translate(mat4(1.0f), vec3(x - 5.0f + sin(time.GetTime()), y - 5.0f, 0.0f));
			mat.SetProperty("worldViewProj", wvp);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
	}

	string title = "FPS " + std::to_string(1.0f / time.GetDelta());
	SetWindowTitle(title.c_str());
}
