#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>
#include <iostream>

#include "game.hpp"


void game::DoStuff(const uint8_t buttons, render &render)
{
	HandleButtons(buttons);
	// UpdatePlayer();
	UpdateEntities();

	render.SetBackground(1, viewportX);
	render.DrawSprites(entityList, viewportX);
}


void game::CreateEntity(EntityType entityType)
{
	entity entity(entityType);
	entityList.push_back(entity);
}


void game::HandleButtons(const uint8_t buttons)
{
	entity &player = entityList[0];

	uint8_t speedX = 0;
	uint8_t speedXfrac = 0;
	uint8_t speedY = 0;
	uint8_t speedYfrac = 0;

	if(buttons & 0b1100)
	{
		speedX = 1;
		speedXfrac = 0x60;

		player.SetFlipX(buttons & 0b0100);
		player.FlipDirectionX(buttons & 0b0100);
	}
	if(buttons & 0b0011)
	{
		speedY = 1;
		speedYfrac = 0x40;
		player.FlipDirectionY(buttons & 0b0001);
	}

	player.SetSpeed(speedX, speedXfrac, speedY, speedYfrac);

	if(buttons & 0b00010000)
	{
		if(viewportX < stageWidth)
		{
			++viewportX;
		}
	}
	if(buttons & 0b00100000)
	{
		if(viewportX)
		{
			--viewportX;
		}
	}
}


void game::UpdatePlayer()
{
}


void game::UpdateEntities()
{
	for(auto &e : entityList)
	{
		if(e.GetSpeed().x || e.GetSpeed().xFrac)
		{
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
