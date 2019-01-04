#pragma once
#include <string>
#include <array>

struct Sprite
{
	std::array<float, 4> rect;
	std::array<float, 4> color;

	Sprite()
	{
		rect = std::array<float, 4>({ 0.25, 0.25, 0.5, 0.5 });
		color = std::array<float, 4>({ 1, 1, 1, 1 });
	}
};

//struct SpriteSheet
//{
//	std::string texName;
//	std::vector<Sprite> sprites;
//
//	SpriteSheet()
//	{
//		sprites.emplace_back();
//	}
//
//	inline std::vector<const char *> GetListboxItems()
//	{
//		std::vector<const char *> result;
//		for (size_t i = 0; i < sprites.size(); i++)
//		{
//			std::string name = "Sprite " + std::to_string(i+1);
//			auto cs = name.c_str();
//			result.push_back(name.c_str());
//		}
//		return result;
//	}
//};
//
