#pragma once
#include <glm/glm.hpp>
#include "Sprite.h"

class GameObject
{
private:
	SpriteHandle spriteID;
	glm::vec3 position;
	//float scale;
public:
	GameObject();
	~GameObject();

	void SetSprite(SpriteHandle _sprite)
	{
		spriteID = _sprite;
	}

	void SetPosition(glm::vec3 _position)
	{
		position = _position;
	}

	SpriteHandle GetSprite()
	{
		return spriteID;
	}

	glm::vec3 GetPosition() const
	{
		return position;
	}
	//void Update();
};

