#pragma once

#include <array>
#include <vector>

#include "entity.hpp"


using PixelArray = std::array<uint16_t, 352*220>;


struct SpriteRect
{
	uint16_t x;
	uint16_t y;
	uint8_t w;
	uint8_t h;
};


class render
{
	public:
		const PixelArray* const GetPixelPtr() const;
		void SetBackground(const uint8_t bg, const uint16_t x);
		void DrawSprites(const std::vector<entity> &entityList);
		void LoadResources();

	private:
		const std::vector<uint16_t> SpriteFromSheet(const std::vector<uint16_t> &spriteSheet, SpriteRect sR, uint8_t flip) const;

		PixelArray screen;
		std::vector<std::vector<uint16_t>> backgrounds;
		std::vector<std::vector<uint16_t>> spriteSheets;

		const std::vector<std::vector<SpriteRect>> spriteRectList
		{
			{ //player
				{0,0,48,80}, {48,0,48,80}, {96,0,48,80}, {144,0,48,80}
			}
		};
};
