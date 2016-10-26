#include <iostream>
#include <vector>
#include <algorithm>

#include "render.hpp"
#include "file.hpp"
#include "animations.hpp"


const PixelArray* const render::GetPixelPtr() const
{
	return &screen;
}


void render::SetBackground(const uint8_t bg, const uint16_t x)
{
	for(uint8_t y = 0; y < 220; ++y)
	{
		std::copy_n(backgrounds[bg].begin() + x + y * bgWidth[bg], 352, screen.begin() + y * 352);
	}
}


void render::LoadResources()
{
	backgrounds.push_back(FileToU16vec("bg1.i15"));
	backgrounds.push_back(FileToU16vec("bg2.i15"));
	spriteSheets.push_back(FileToU16vec("spr1.i15"));
	spriteSheets.push_back(FileToU16vec("spr2.i15"));
}


void render::DrawSprites(const std::vector<entity> &entityList, const uint16_t viewportX)
{
	//use viewportX

	for(const auto &e : entityList)
	{
		const uint16_t &type = e.GetEntityType();

		const EntityState &state = e.GetEntityState();
		const uint8_t &w = spriteRectList[type][state.action].w;
		const uint8_t &h = spriteRectList[type][state.action].h;

		const Position &pos = e.GetPosition();

		const std::vector<uint16_t> sprite = SpriteFromSheet(spriteSheets[type], spriteRectList[type][animationList[type][state.action][state.animState]], e.GetFlip(), sheetWidth[type]);

		for(uint16_t y = 0; y < h; ++y)
		{
			for(uint16_t x = 0; x < w; ++x)
			{
				if(sprite[x + y * w] & 1)
				{
					if(uint16_t(pos.x - viewportX + x) < 352 && uint16_t(pos.y + y) < 220)
					{
						screen[uint16_t(pos.x - viewportX + x) + uint16_t(pos.y + y) * 352] = sprite[x + y * w];
					}
				}
			}
		}
	}
}


const std::vector<uint16_t> render::SpriteFromSheet(const std::vector<uint16_t> &spriteSheet, SpriteRect sR, const uint8_t flip, uint16_t sheetW) const
{
	const uint8_t w = sR.w;
	const uint8_t h = sR.h;

	std::vector<uint16_t> sprite(w * h);
	const bool flipX = flip & 1;
	const bool flipY = flip & 2;

	auto iter1 = spriteSheet.begin() + sR.x + sR.y * sheetW;

	if(!flipX)
	{
		for(uint16_t y; y < h; ++y)
		{
			std::copy_n(iter1 + y * sheetW, w, sprite.begin() + y * w);
		}
	}
	else
	{
		for(uint16_t y; y < h; ++y)
		{
			std::reverse_copy(iter1 + y * sheetW, iter1 + y * sheetW + w, sprite.begin() + y * w);
		}
	}

	if(flipY)
	{
		std::vector<uint16_t> flippedY(w * h);
		auto iter2 = sprite.begin() + sR.h * w;
		for(uint16_t y = 0; y < h; ++y)
		{
			std::copy_n(iter2 - y * w, w, flippedY.begin() + y*w);
		}
		sprite = flippedY;
	}

	return sprite;
}
