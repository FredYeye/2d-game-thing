#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>
#include <iostream>

#include "game.hpp"
#include "file.hpp"
// #include "animations.hpp"


void game::DoStuff(const uint8_t buttons, render &render)
{
	HandleButtons(buttons);
	UpdatePlayer();

	render.SetBackground(0, 0);
	render.DrawSprites(entityList);
}


void game::CreateEntity(EntityType entityType)
{
	entity entity(entityType);
	entityList.push_back(entity);
}


void game::HandleButtons(const uint8_t buttons)
{
	entity &player = entityList[0];

	int8_t speedX = -((buttons & 0x04) >> 2) + ((buttons & 0x08) >> 3);
	int8_t speedY = -((buttons & 0x01)     ) + ((buttons & 0x02) >> 1);
	player.SetSpeed(speedX, speedY);

	if(speedX)
	{
		player.SetFlipX(uint8_t(speedX) >> 7);
		player.SetEntityAction(EntityAction::walking);
	}
	else
	{
		player.SetEntityAction(EntityAction::idle);
	}
}


void game::UpdatePlayer()
{
	Speed speed = entityList[0].GetSpeed();
	entityList[0].SetRelativePosition(speed.x, speed.y);
}
