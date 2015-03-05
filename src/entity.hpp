#pragma once


enum class EntityType : uint16_t{player = 0, crate};
enum class EntityAction : uint8_t{idle = 0, walking};


struct Position
{
	uint16_t x = 0;
	uint16_t y = 0;
	uint16_t z = 0;
};


struct Speed
{
	int8_t x = 0;
	int8_t y = 0;
	int8_t z = 0;
};


struct EntityState
{
	EntityAction action = EntityAction::idle;
	uint8_t animFrame = 0;
	uint8_t animState = 0;
};


class entity
{
	public:
		entity(EntityType type);
		void SetPosition(const uint16_t x, const uint16_t y);
		const Position& GetPosition() const;
		void SetRelativePosition(const int16_t x, const int16_t y);
		void SetSpeed(const int8_t x, const int8_t y);
		const Speed& GetSpeed() const;
		void SetFlipX(bool flipX);
		void SetFlipY(bool flipY);
		const uint8_t GetFlip() const;
		const EntityType GetEntityType() const;
		void SetEntityAction(EntityAction action);
		EntityAction GetEntityAction() const;
		// const uint8_t GetAnimState() const;
		// const uint8_t GetAnimFrame() const;
		// void UpdateAnim(const uint8_t entityIndex);

	private:
		Position position;
		Speed speed;
		uint8_t flip = 0; //bit 0:x flip  bit 1:y flip
		EntityType entityType;
		EntityState entityState;
};
