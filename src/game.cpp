#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>
#include <iostream>

#include "game.hpp"
#include "file.hpp"


void game::DoStuff(const uint8_t buttons, render &render)
{
	HandleButtons(buttons);
	// UpdatePlayer();
	UpdateEntities();

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
}


void game::UpdatePlayer()
{
}


void game::UpdateEntities()
{
	for(auto &e : entityList)
	{
		int8_t speedX = e.GetSpeed().x;
		if(speedX)
		{
			e.SetFlipX(uint8_t(speedX) >> 7);
			e.SetEntityAction(EntityAction::walking);
		}
		else
		{
			e.SetEntityAction(EntityAction::idle);
		}

		e.UpdatePos();
		e.UpdateAnim();
	}
}
