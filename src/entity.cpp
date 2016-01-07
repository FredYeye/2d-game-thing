#include <cstdint>

#include "entity.hpp"
#include "render.hpp"
#include "animations.hpp"


entity::entity(EntityType type) : entityType(type)
{
}


void entity::SetPosition(const uint16_t x, const uint16_t y, const uint8_t z)
{
	position.x = x;
	position.y = y;
	position.z = z;

	position.xFrac = 0;
	position.yFrac = 0;
	position.zFrac = 0;
}


const Position& entity::GetPosition() const
{
	return position;
}


void entity::SetRelativePosition(const int16_t x, const int16_t y)
{
	position.x += x;
	position.y += y;
}


void entity::SetSpeed(const uint8_t x, const uint8_t xFrac, const uint8_t y, const uint8_t yFrac)
{
	speed.x = x;
	speed.xFrac = xFrac;
	speed.y = y;
	speed.yFrac = yFrac;
}


const Speed& entity::GetSpeed() const
{
	return speed;
}


void entity::SetFlipX(bool flipX)
{
	flip = (flip & 2) | flipX;
}


void entity::SetFlipY(bool flipY)
{
	flip = (flip & 1) | (flipY << 1);
}


const uint8_t entity::GetFlip() const
{
	return flip;
}


void entity::FlipDirectionX(bool xDir)
{
	direction = (direction & 2) | xDir;
}


void entity::FlipDirectionY(bool yDir)
{
	direction = (direction & 1) | (yDir << 1);
}


const EntityType entity::GetEntityType() const
{
	return entityType;
}


void entity::SetEntityAction(EntityAction action)
{
	if(action != entityState.action)
	{
		entityState.action = action;
		entityState.animFrame = 0;
		entityState.animState = 0;
	}
}


const EntityState& entity::GetEntityState() const
{
	return entityState;
}


void entity::UpdateAnim()
{
	if(!frameList[entityType][uint8_t(entityState.action)].empty())
	{
		if(++entityState.animFrame > frameList[entityType][uint8_t(entityState.action)][entityState.animState])
		{
			entityState.animFrame = 0;
			if(++entityState.animState == animationList[entityType][uint8_t(entityState.action)].size())
			{
				entityState.animState = 0;
			}
		}
	}
}


void entity::UpdatePos()
{
	if(!(direction & 1))
	{
		position.x += speed.x + (position.xFrac + speed.xFrac >> 8);
		position.xFrac += speed.xFrac;
	}
	else
	{
		position.xFrac -= speed.xFrac;
		position.x -= speed.x + (position.xFrac + speed.xFrac >> 8);
	}

	if(!(direction & 2))
	{
		position.y += speed.y + (position.yFrac + speed.yFrac >> 8);
		position.yFrac += speed.yFrac;
	}
	else
	{
		position.yFrac -= speed.yFrac;
		position.y -= speed.y + (position.yFrac + speed.yFrac >> 8);
	}
}
