#pragma once
#include <glm/glm.hpp>
#include "App.h"
#include "Material.h"
#include "Common.h"
#include "Camera.h"
#include <glm/ext.hpp>
#include "ContentManager.h"
#include "Sprite.h"

using namespace glm;

struct Vertex
{
	vec3 position;
	vec2 tex;
	vec4 color;
};
// Should be responsibility of the renderer
struct Quad
{
	GLuint vao;
	union
	{
		struct
		{
			GLuint vBuffer;
			GLuint iBuffer;
		};
		GLuint buffers[2];
	};

	void Init()
	{
		Vertex vertices[4];

		vertices[0].position = vec3(-0.5f, -0.5f, 0.0f);
		vertices[1].position = vec3(-0.5f, 0.5f, 0.0f);
		vertices[2].position = vec3(0.5f, 0.5f, 0.0f);
		vertices[3].position = vec3(0.5f, -0.5f, 0.0f);

		vertices[0].tex = vec2(0.0f, 0.0f);
		vertices[1].tex = vec2(0.0f, 1.0f);
		vertices[2].tex = vec2(1.0f, 1.0f);
		vertices[3].tex = vec2(1.0f, 0.0f);

		vertices[0].color = vec4(1.0f, 0.05f, 0.05f, 1.0f);
		vertices[1].color = vec4(0.05f, 1.0f, 0.05f, 1.0f);
		vertices[2].color = vec4(0.05f, 0.05f, 1.0f, 1.0f);
		vertices[3].color = vec4(0.9f, 0.9f, 0.9f, 1.0f);

		uint indices[6] = {
			0, 1, 2,
			0, 2, 3
		};

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Gen VB and IB at the same time
		glGenBuffers(2, buffers);
		glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, tex));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void Bind()
	{
		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer);
	}
};

class Game :
	public App
{
private:
	ContentManager content;
	Camera cam;
	Quad quad;
	Material mat;
	Sprite cactusSprite;
public:
	Game() : App() {}
	~Game();

protected:
	// Inherited via App
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Draw() override;
};

