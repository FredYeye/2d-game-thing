#pragma once

#include "entity.hpp"
#include "render.hpp"


class game
{
	public:
		void DoStuff(const uint8_t buttons, render &render);
		void CreateEntity(EntityType entityType);
		void HandleButtons(const uint8_t buttons);
		void UpdatePlayer();
		void UpdateEntities();

	private:
		std::vector<entity> entityList;
};
