#pragma once


enum EntityType : uint16_t{player = 0, thing};
enum EntityAction : uint8_t{idle = 0, walking};


struct Position
{
	uint16_t x = 0;
	uint8_t  xFrac = 0;
	uint16_t y = 0;
	uint8_t  yFrac = 0;
	uint8_t  z = 0;
	uint8_t  zFrac = 0;
};


struct Speed
{
	uint8_t x = 0;
	uint8_t xFrac = 0;
	uint8_t y = 0;
	uint8_t yFrac = 0;
	uint8_t z = 0;
	uint8_t zFrac = 0;
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

		void SetPosition(const uint16_t x, const uint16_t y, const uint8_t z);
		const Position& GetPosition() const;
		void SetRelativePosition(const int16_t x, const int16_t y);
		void SetSpeed(const uint8_t x, const uint8_t xFrac, const uint8_t y, const uint8_t yFrac);
		const Speed& GetSpeed() const;

		void SetFlipX(bool flipX);
		void SetFlipY(bool flipY);
		const uint8_t GetFlip() const;
		void FlipDirectionX(bool xDir);
		void FlipDirectionY(bool yDir);

		const EntityType GetEntityType() const;
		void SetEntityAction(EntityAction action);
		const EntityState& GetEntityState() const;

		void UpdateAnim();
		void UpdatePos();

	private:
		Position position;
		Speed speed;
		uint8_t direction = 0; //bit 0:x bit 1:y
		uint8_t flip = 0; //bit 0:x flip  bit 1:y flip
		EntityType entityType;
		EntityState entityState;
};
