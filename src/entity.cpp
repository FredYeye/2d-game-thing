#include <cstdint>

#include "entity.hpp"
#include "render.hpp"
#include "animations.hpp"


entity::entity(EntityType type)
{
	entityType = type;
}


void entity::SetPosition(const uint16_t x, const uint16_t y)
{
	position.x = x;
	position.y = y;
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


void entity::SetSpeed(const int8_t x, const int8_t y)
{
	speed.x = x;
	speed.y = y;
}


const Speed& entity::GetSpeed() const
{
	return speed;
}


void entity::SetFlipX(bool flipX)
{
	flip = (flip & 2) | uint8_t(flipX);
}


void entity::SetFlipY(bool flipY)
{
	flip = (flip & 1) | (uint8_t(flipY) << 1);
}


const uint8_t entity::GetFlip() const
{
	return flip;
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
	if(!frameList[uint16_t(entityType)][uint8_t(entityState.action)].empty())
	{
		if(++entityState.animFrame > frameList[uint16_t(entityType)][uint8_t(entityState.action)][entityState.animState])
		{
			entityState.animFrame = 0;
			if(++entityState.animState == animationList[uint16_t(entityType)][uint8_t(entityState.action)].size())
			{
				entityState.animState = 0;
			}
		}
	}
}


void entity::UpdatePos()
{
	position.x += speed.x;
	position.y += speed.y;
}
