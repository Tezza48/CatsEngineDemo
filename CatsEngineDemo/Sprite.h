#pragma once
#include <GL/glew.h>
#include "Maths.h"

// texture atlas and coords
class Sprite
{
// Texture : atlas
Rect spriteRect;
public:
	Sprite();
	~Sprite();

	void Init();
};

