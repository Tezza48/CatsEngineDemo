#pragma once
#include <string>
#include <vector>

struct Sprite
{
	union
	{
		float *_val;
		struct
		{
			float rect[4];
			float color[4];
		};
	};
	Sprite()
	{
		float def[8] = { 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
		_val = def;
	}
};

struct SpriteSheet
{
	std::string texName;
	std::vector<Sprite> sprites;

	SpriteSheet()
	{
		sprites.emplace_back();
	}

	inline std::vector<const char *> GetListboxItems()
	{
		std::vector<const char *> result;
		for (size_t i = 0; i < sprites.size(); i++)
		{
			std::string name = "Sprite " + std::to_string(i+1);
			auto cs = name.c_str();
			result.push_back(name.c_str());
		}
		return result;
	}
};

