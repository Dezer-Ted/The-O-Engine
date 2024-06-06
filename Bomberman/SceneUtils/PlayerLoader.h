#pragma once
#include <SDL_rect.h>

#include "../GridComponent.h"
#include "SceneObjects/GameObject.h"

namespace dae
{
	class PlayerLoader {
	public:
		static dae::GameObject* LoadPlayer(Scene* pScene,const SDL_Rect&  levelBounds,GridComponent* pGrid);
	};
}
