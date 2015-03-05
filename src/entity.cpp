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
	entityState.action = action;
}

EntityAction entity::GetEntityAction() const
{
	return entityState.action;
}

// const uint8_t entity::GetAnimState() const
// {
	// return entityState.animState;
// }

// const uint8_t entity::GetAnimFrame() const
// {
	// return entityState.animFrame;
// }

// void entity::UpdateAnim(const uint8_t entityIndex)
// {

// }
