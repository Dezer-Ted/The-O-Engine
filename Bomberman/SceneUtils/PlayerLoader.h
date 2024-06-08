#pragma once
#include <SDL_rect.h>

#include "../GridComponent.h"
#include "SceneObjects/GameObject.h"



namespace dae
{
	class PowerUpComponent;

	class PlayerLoader {
	public:
		static dae::GameObject* LoadPlayer(Scene* pScene, const SDL_Rect& levelBounds, GridComponent* pGrid, const std::string& playerName);
	private:
		static PowerUpComponent* LoadUpgrades(GameObject* pPlayer);
	};
}
